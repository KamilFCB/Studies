#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

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

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))

(define (hole-context e)
  ;; TODO: zaimplementuj!
  (define (iter e acc)
    (cond [(or (not (arith/let/hole-expr? e))
               (hole? e)) acc]
          [(binop? e) (if (arith/let/hole-expr? (binop-left e))
                          (iter (binop-left e) acc)
                          (iter (binop-right e) acc))]
          [(let? e) (cond [(hole? (let-def-expr (let-def e))) acc]
                          [(arith/let/hole-expr? (let-def-expr (let-def e)))
                           (iter (let-def-expr (let-def e)) acc)]
                          [(member (let-def-var (let-def e)) acc)
                           (iter (let-expr e) acc)]
                          [else (iter (let-expr e)
                                      (cons (let-def-var (let-def e)) acc))])]
          [(var? e) (if (member e acc)
                        acc
                        (cons e acc))]))
  (iter e null))



(define (test)
  ;; TODO: zaimplementuj!
  (define (check-answer res ans)
    (cond [(eq? res ans) (displayln true)]
          [(member (car res) ans) (check-answer (cdr res) (remove (car res) ans))]
          [else (displayln false)]))
  
  (check-answer (hole-context '(+ 3 hole)) '())
  (check-answer (hole-context '(let (x 3) (let (y 7) (+ x hole)))) '(y x))
  (check-answer (hole-context '(let (x 3) (let (y hole ) (+ x 3)))) '(x))
  (check-answer (hole-context '(let (x hole) (let (y 7) (+ x 3)))) '())
  (check-answer (hole-context '(let (piesek 1)
                     (let (kotek 7)
                        (let (piesek 9)
                           (let (chomik 5)
                              hole))))) '(piesek kotek chomik))
  (check-answer (hole-context '(+ (let (x 4) 5) hole)) '())
  (check-answer (hole-context '(/ (* 1 (let (x 4) 3)) (let (z 2) hole))) '(z))
  (check-answer (hole-context '(+ x hole)) '())
  (check-answer (hole-context '(let (x 10)
                                 (let (y 10)
                                   (let (z hole) 42)))) '(x y))
  (check-answer (hole-context '(let (x y)
                                 (let (z 3) hole))) '(x z))
  (check-answer (hole-context '(+ y (* z (/ x hole)))) '())
  (check-answer (hole-context '(+ 1 (* 2 (/ 3 (- 3 hole))))) '())
  (check-answer (hole-context '(let (a 1)
                                 (let (c 2)
                                   (let (b 11)
                                     (+ 1 (* 2 (/ 3 (- 3 hole)))))))) '(a b c))
  (check-answer (hole-context '(let (x (+ y hole)))) '()))

(test)