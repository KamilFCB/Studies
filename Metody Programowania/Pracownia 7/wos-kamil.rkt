#lang racket

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op-cons op args)
  (cons op args))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (arith/let-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith/let-expr? (op-args t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def-expr (let-def t))))
      (var? t)))

;; let-lifted expressions

(define (arith-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith-expr? (op-args t)))
      (var? t)))

(define (let-lifted-expr? t)
  (or (and (let? t)
           (let-lifted-expr? (let-expr t))
           (arith-expr? (let-def-expr (let-def t))))
      (arith-expr? t)))

;; generating a symbol using a counter

(define (number->symbol i)
  (string->symbol (string-append "x" (number->string i))))

;; environments (could be useful for something)

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

;; the let-lift procedure

(define (let-lift e)
  ;; TODO: Zaimplementuj!
  (define (list-of-pairs ls)
    (if (null? ls)
        null
        (cons (list (car ls) (cadr ls))
              (list-of-pairs (cddr ls)))))
  
  (define (make-new-expr vars expr)
    (if (null? vars)
        expr
        (let-cons (car vars) (make-new-expr (cdr vars) expr))))

  (define (iter args counter defs-acc args-acc env)
    (if (null? args)
        (cons (list defs-acc args-acc) counter)
        (let* ([rec-res (let-lift-rec (car args) counter env)]
               [new-counter (cdr rec-res)]
               [new-defs (caar rec-res)]
               [new-args (cadar rec-res)])
          (iter (cdr args) new-counter (flatten (append defs-acc new-defs)) (append args-acc (list new-args)) env))))
        
  (define (let-lift-rec e counter env)
    (cond [(const? e) (cons (list '() e) counter)]
          [(var? e) (cons (list '() (find-in-env e env)) counter)]
          [(op? e)
           (let ([res (iter (op-args e) counter null null env)])
             (cons (list (flatten (caar res)) (op-cons (op-op e) (cadar res))) (cdr res)))]
          [(let? e)
           (let* ([def (let-def e)]
                  [new-var (number->symbol counter)]
                  [new-env (add-to-env (let-def-var def) new-var env)]
                  [new-let-def-expr (let-lift-rec (let-def-expr def) (+ counter 1) env)]
                  [cos (let-lift-rec (let-expr e) (cdr new-let-def-expr) new-env)]
                  [next-defs (if (null? (caar cos)) '() (caar cos))]
                  [next-args (cadar cos)]
                  [new-defs (append (caar new-let-def-expr) (list new-var (cadar new-let-def-expr)) next-defs)])
             (cons (list new-defs next-args) (cdr cos)))]))
  
  (let ([res (let-lift-rec e 1 empty-env)])
    (make-new-expr (list-of-pairs (caar res)) (cadar res))))

; tests

(let-lift '(let (x (- 2 (let (z (let (a 2) 3)) z))) (+ x 2)))
(let-lift '(+ ( let (x 5) x) ( let (x 1) x)))
(let-lift '(let (x 2) (let (x 4) x)))
(let-lift '(let (x (- 2 (let (z 3) z))) (+ x 2)))
(let-lift '(+ 10 (* (let (x 7) (+ x 2)) 2)))
(let-lift '(+ 10 (* 2 3 4 5) (- 20 1)))
(let-lift '(+ (let (x 10) x) (* (let (z 2) z) (let (y 4) y)) (let (a 20) (- a 1))))
(let-lift '(let (x (- 2 (let (z (let (a 2) 3)) z))) (+ x (let (y 2) (let (w 20) (+ y w))))))
