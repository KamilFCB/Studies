#lang racket

(define (inc n)
  (+ n 1))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (list? h)
       (= 5 (length h))
       (eq? (car h) 'hnode)
       (natural? (caddr h))))

(define (make-node elem heap-a heap-b)
  ;;; XXX: fill in the implementation
  (let ([rank-left (inc (rank heap-a))]
        [rank-right (inc (rank heap-b))])
    (if (< rank-left rank-right)
        (list 'hnode elem rank-left heap-b heap-a)
        (list 'hnode elem rank-right heap-a heap-b))))

(define (node-elem h)
  (second h))

(define (node-left h)
  (fourth h))

(define (node-right h)
  (fifth h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (node-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (node-left h))
           (heap? (node-right h))
           (<= (rank (node-right h))
               (rank (node-left h)))
           (= (rank h) (inc (rank (node-right h))))
           (hord? (elem-priority (node-elem h))
                  (node-left h))
           (hord? (elem-priority (node-elem h))
                  (node-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (third h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-node elt leaf leaf)))

(define (heap-min heap)
  (node-elem heap))

(define (heap-pop heap)
  (heap-merge (node-left heap) (node-right heap)))

(define (heap-merge h1 h2)
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [else (let ([h1-min (heap-min h1)]
               [h2-min (heap-min h2)])
           (let ([h1-prior (elem-priority h1-min)]
                 [h2-prior (elem-priority h2-min)])           
           (if (< h1-prior h2-prior)
               (make-node h1-min (heap-merge (node-right h1) h2) (node-left h1))
               (make-node h2-min (heap-merge (node-right h2) h1) (node-left h2))))
               )]))


;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))


;testy

(define l1 (randlist 10 20))
(define l2 (randlist 100 20))
(define l3 (randlist 1000 50))
(define l4 (randlist 10000 500))
(define l5 (randlist 10000 10))
(define l6 (randlist 100000 1000))
(define l7 (randlist 100000 10))

(sorted? (heapsort l1))
(sorted? (heapsort l2))
(sorted? (heapsort l3))
(sorted? (heapsort l4))
(sorted? (heapsort l5))
(sorted? (heapsort l6))
(sorted? (heapsort l7))