#lang racket



; dodanie modulu testow
(require rackunit)

(define (dist x y)
  (abs (- x y)))

(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(define (cube-root x)
  (define (improve y)
    (/ (+ (/ x (square y)) (+ y y)) 3))
  (define (good-enough? approx)
    (< (dist x (cube approx)) 0.0000001))
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))



; testy

(check-equal? (cube-root 0.00001977215) 0.02705449107958573 "Bledny wynik!")
(check-equal? (cube-root 0.00512811) 0.17244572964757157 "Bledny wynik!")
(check-equal? (cube-root 0.01) 0.21544348341456257 "Bledny wynik!")
(check-equal? (cube-root 0.03) 0.31072330481596677 "Bledny wynik!")
(check-equal? (cube-root 0.2151) 0.5991655065764926 "Bledny wynik!")
(check-equal? (cube-root 0.918251) 0.9719721099330373 "Bledny wynik!")
(check-equal? (cube-root 1) 1.0 "Bledny wynik!")
(check-equal? (cube-root 2) 1.2599210500177698 "Bledny wynik!")
(check-equal? (cube-root 3) 1.4422495703074416 "Bledny wynik!")
(check-equal? (cube-root 4) 1.5874010520152708 "Bledny wynik!")
(check-equal? (cube-root 5) 1.709975950782189 "Bledny wynik!")
(check-equal? (cube-root 6) 1.817120592832144 "Bledny wynik!")
(check-equal? (cube-root 7) 1.912931182772774 "Bledny wynik!")
(check-equal? (cube-root 8) 2.000000000012062 "Bledny wynik!")
(check-equal? (cube-root 9) 2.0800838232385224 "Bledny wynik!")
(check-equal? (cube-root 10) 2.154434691772293 "Bledny wynik!")
(check-equal? (cube-root 13) 2.3513346877207755 "Bledny wynik!")
(check-equal? (cube-root 15) 2.466212074331816 "Bledny wynik!")
(check-equal? (cube-root 18) 2.6207413943668505 "Bledny wynik!")
(check-equal? (cube-root 21) 2.7589241763811203 "Bledny wynik!")
(check-equal? (cube-root 27) 3.0000000000000977 "Bledny wynik!")
(check-equal? (cube-root 33) 3.207534330033711 "Bledny wynik!")
(check-equal? (cube-root 42) 3.4760266448864496 "Bledny wynik!")
(check-equal? (cube-root 213) 5.972092619857956 "Bledny wynik!")
(check-equal? (cube-root 512) 8.0 "Bledny wynik!")
(check-equal? (cube-root 871) 9.550058934424278 "Bledny wynik!")
(check-equal? (cube-root 1592) 11.676544921628006 "Bledny wynik!")
(check-equal? (cube-root 9215) 20.96517280986635 "Bledny wynik!")
(check-equal? (cube-root 37251) 33.397399011005 "Bledny wynik!")
(check-equal? (cube-root 8215923) 201.78340833840085 "Bledny wynik!")


