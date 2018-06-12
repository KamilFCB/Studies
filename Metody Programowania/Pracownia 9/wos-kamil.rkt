#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;;
;; WHILE
;;

; memory

(define empty-mem
  null)

(define (set-mem x v m)
  (cond [(null? m)
         (list (cons x v))]
        [(eq? x (caar m))
         (cons (cons x v) (cdr m))]
        [else
         (cons (car m) (set-mem x v (cdr m)))]))

(define (get-mem x m)
  (cond [(null? m) 0]
        [(eq? x (caar m)) (cdar m)]
        [else (get-mem x (cdr m))]))

; arith and bool expressions: syntax and semantics

(define (const? t)
  (number? t))

(define (true? t)
  (eq? t 'true))

(define (false? t)
  (eq? t 'false))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= not and or mod rand expt))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]
        [(eq? op 'not) not]
        [(eq? op 'and) (lambda x (andmap identity x))]
        [(eq? op 'or) (lambda x (ormap identity x))]
        [(eq? op 'mod) modulo]
        [(eq? op 'expt) expt]
        [(eq? op 'rand) (lambda (max) (min max 4))])) ; chosen by fair dice roll.
                                                      ; guaranteed to be random.


(define (var? t)
  (symbol? t))

(define (eval-arith e m)
  (cond [(true? e) true]
        [(false? e) false]
        [(var? e) (get-mem e m)]
        [(op? e)
         (apply
          (op->proc (op-op e))
          (map (lambda (x) (eval-arith x m))
               (op-args e)))]
        [(const? e) e]))

;; syntax of commands

(define (assign? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (second t) ':=)))

(define (assign-var e)
  (first e))

(define (assign-expr e)
  (third e))

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

(define (while? t)
  (tagged-tuple? 'while 3 t))

(define (while-cond t)
  (second t))

(define (while-expr t)
  (third t))

(define (block? t)
  (list? t))

(define (rand? t)
  (tagged-tuple? 'rand 2 t))

(define (rand-expr t)
  (second t))

;; state

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;; psedo-random generator

(define initial-seed
  123456789)

(define (rand max)
  (lambda (i)
    (let ([v (modulo (+ (* 1103515245 i) 12345) (expt 2 32))])
      (res (modulo v max) v))))

;; WHILE interpreter

(define (old-eval e m)
  (cond [(assign? e)
         (set-mem
          (assign-var e)
          (eval-arith (assign-expr e) m)
          m)]
        [(if? e)
         (if (eval-arith (if-cond e) m)
             (old-eval (if-then e) m)
             (old-eval (if-else e) m))]
        [(while? e)
         (if (eval-arith (while-cond e) m)
             (old-eval e (old-eval (while-expr e) m))
             m)]
        [(block? e)
         (if (null? e)
             m
             (old-eval (cdr e) (old-eval (car e) m)))]))

(define (eval-arith-with-seed e m)  
  (if (rand? e)      
      (let* ((res (eval-arith-with-seed (rand-expr e) m))
             (rand-res ((rand (car res)) (get-mem 'seed (cdr res)))))
        (cons (car rand-res) (set-mem 'seed (cdr rand-res) (cdr res))))
      (new-eval-arith e m)))

(define (new-eval-arith e m)
  (cond [(true? e) (cons true m)]
        [(false? e) (cons false m)]
        [(var? e) (cons (get-mem e m) m)]
        [(op? e)
          (apply-args (op-args e) (op-op e) m)]
        [(const? e) (cons e m)]))

(define (apply-args args op m)
  (define (iter args res m)
    (if (null? args)
        (cons res m)
        (let ((tmp-res (eval-arith-with-seed (car args) m)))
          (iter (cdr args) (append res (list (car tmp-res))) (cdr tmp-res)))))
  (let ((res (iter args null m)))
    (cons (apply (op->proc op) (car res)) (cdr res))))

(define (eval e m seed)
  ;; TODO : ZAD B: Zaimplementuj procedurę eval tak, by
  ;;        działała sensownie dla wyrażeń używających
  ;;        konstrukcji "rand".
  (define (rec e m)
    (cond [(assign? e)
           (let ((res (eval-arith-with-seed (assign-expr e) m)))
             (set-mem
              (assign-var e)
            (car res)
            (cdr res)))]
          [(if? e)
           (let* ((res (eval-arith-with-seed (if-cond e) m))
                  (new-mem (cdr res)))
             (if (car res)
                 (rec (if-then e) new-mem)
                 (rec (if-else e) new-mem)))]
          [(while? e)
           (let* ((res (eval-arith-with-seed (while-cond e) m))
                  (new-mem (cdr res)))
             (if (car res)
                 (rec e (rec (while-expr e) new-mem))
                 new-mem))]
          [(block? e)
           (if (null? e)
               m
               (rec (cdr e) (rec (car e) m)))]))
  (rec e (set-mem 'seed seed m)))


(define (run e)
  (eval e empty-mem initial-seed))

;;

(define fermat-test
  '{(composite := false)
    (while (> k 0)
      ( ( a := (+ 2 (rand (- n 3))))
        (if (not (= (mod (expt a (- n 1)) n) 1))
            ( (k := 0)
              (composite := true) )
            (k := (- k 1)))
        ))
    } ;; TODO : ZAD A: Zdefiniuj reprezentację programu w jęzku
      ;;        WHILE, który wykonuje test Fermata, zgodnie z
      ;;        treścią zadania. Program powinien zakładać, że
      ;;        uruchamiany jest w pamięci, w której zmiennej
      ;;        n przypisana jest liczba, którą testujemy, a
      ;;        zmiennej k przypisana jest liczba iteracji do
      ;;        wykonania. Wynik powinien być zapisany w
      ;;        zmiennej comopsite. Wartość true oznacza, że
      ;;        liczba jest złożona, a wartość false, że jest
      ;;        ona prawdopodobnie pierwsza.
  )

(define (probably-prime? n k) ; check if a number n is prime using
                              ; k iterations of Fermat's primality
                              ; test
  (let ([memory (set-mem 'k k
                (set-mem 'n n empty-mem))])
    (not (get-mem
           'composite
           (eval fermat-test memory initial-seed)))))


(displayln "pierwsze:")
(probably-prime? 5 112)
(probably-prime? 7 21)
(probably-prime? 757 125)
(probably-prime? 2131 189)
(probably-prime? 2467 661)
(probably-prime? 4733 1612)
(probably-prime? 6659 931)
(probably-prime? 11953 601)
(displayln "złożone")
(probably-prime? 8 17)
(probably-prime? 9 23)
(probably-prime? 63 42)
(probably-prime? 100 56)
(probably-prime? 21512 33)
(probably-prime? 98653 96)