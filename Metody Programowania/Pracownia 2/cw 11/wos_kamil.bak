#lang racket
(require rackunit)

(define (dist x y)
  (abs (- x y)))

(define (inc i)
  (+ i 1))

(define (dec x)
  (- x 1))

(define (identity x) x)

(define (nth-root x n)
  (define (repeated p n)
    (if (= n 0)
      (identity p)
      (compose p (repeated p (- n 1)))))
  
  (define (average-damp f)
    (lambda (x) (/ (+ x (f x)) 2)))

  (define (fixed-point f x0)
    (let ((x1 (f x0)))
      (if (close-enough? x0 x1)
          x0
          (fixed-point f x1))))
  
  (define (close-enough? x y)
    (< (dist x y) 0.0000000001))

  ; ilość tłumień to podłoga z logarytmu o podstawie 2 ze stopnia pierwiastka
  (define (ilosc-tlumien)
    (floor (log n 2)))
  
  (if (= x 0)
      0
      (fixed-point ((repeated average-damp (ilosc-tlumien)) (lambda (y) (/ x (expt y (dec n))))) 1.0)))


(check-equal? (nth-root -2 3) -1.2599210499450761 "Bledny wynik!")
(check-equal? (nth-root 15 7) 1.4723567002070355 "Bledny wynik!")
(check-equal? (nth-root 0.00000000051257 13) 0.1929148367512219 "Bledny wynik!")
(check-equal? (nth-root 31245 5) 7.924212363226548 "Bledny wynik!")
(check-equal? (nth-root 251 2) 15.842979517953538 "Bledny wynik!")
(check-equal? (nth-root 678915251 23) 2.420984344752202 "Bledny wynik!")
(check-equal? (nth-root 3 2) 1.7320508073818108 "Bledny wynik!")
(check-equal? (nth-root 1899 5) 4.525900406366147 "Bledny wynik!")
(check-equal? (nth-root 10 14) 1.1787686348401514 "Bledny wynik!")
(check-equal? (nth-root 2 53) 1.0131641431023355 "Bledny wynik!")
