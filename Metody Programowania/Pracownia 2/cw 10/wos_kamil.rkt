#lang racket
(require rackunit)

(define (dist x y)
  (abs (- x y)))

(define (inc x)
  (+ x 1))

(define (dec x)
  (- x 1))

(define (square x)
  (* x x))

(define (cont-frac n d )
  (define (iter x an-1 an-2 bn-1 bn-2 fk-1)
    (let ([an (+ (* (d x) an-1) (* (n x) an-2))]
          [bn (+ (* (d x) bn-1) (* (n x) bn-2))])
          (let ([fk (/ an bn)])
    (if (< (dist fk fk-1) 0.00000000001)
        fk
        (iter (inc x) an an-1 bn bn-1 fk)))))
  
  (iter 1 0.0 1.0 1.0 0.0 0.0))


(check-equal? (cont-frac (lambda (x) 1.0) (lambda (x) 1.0)) 0.6180339887482036 "Bledny wynik!")
(check-equal? (cont-frac (lambda (x) x) (lambda (x) x)) 0.5819767068692134 "Bledny wynik!")
(check-equal? (cont-frac (lambda(x) x) (lambda(x) (+ x 2))) 0.2906166927858349 "Bledny wynik!")
(check-equal? (cont-frac (lambda (x) 6.0) (lambda (x) (square (+ x (dec x))))) 3.637614217534802 "Bledny wynik!")
(check-equal? (cont-frac (lambda (x) 2.0) (lambda (x) 8.0)) 0.2426406871191443 "Bledny wynik!")
