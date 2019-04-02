#lang racket

;; sygnatura: grafy
(define-signature graph^
  ((contracted
    [graph        (-> list? (listof edge?) graph?)]
    [graph?       (-> any/c boolean?)]
    [graph-nodes  (-> graph? list?)]
    [graph-edges  (-> graph? (listof edge?))]
    [edge         (-> any/c any/c edge?)]
    [edge?        (-> any/c boolean?)]
    [edge-start   (-> edge? any/c)]
    [edge-end     (-> edge? any/c)]
    [has-node?    (-> graph? any/c boolean?)]
    [outnodes     (-> graph? any/c list?)]
    [remove-node  (-> graph? any/c graph?)]
    )))

;; prosta implementacja grafów
(define-unit simple-graph@
  (import)
  (export graph^)

  (define (graph? g)
    (and (list? g)
         (eq? (length g) 3)
         (eq? (car g) 'graph)))

  (define (edge? e)
    (and (list? e)
         (eq? (length e) 3)
         (eq? (car e) 'edge)))

  (define (graph-nodes g) (cadr g))

  (define (graph-edges g) (caddr g))

  (define (graph n e) (list 'graph n e))

  (define (edge n1 n2) (list 'edge n1 n2))

  (define (edge-start e) (cadr e))

  (define (edge-end e) (caddr e))

  (define (has-node? g n) (not (not (member n (graph-nodes g)))))
  
  (define (outnodes g n)
    (filter-map
     (lambda (e)
       (and (eq? (edge-start e) n)
            (edge-end e)))
     (graph-edges g)))

  (define (remove-node g n)
    (graph
     (remove n (graph-nodes g))
     (filter
      (lambda (e)
        (not (eq? (edge-start e) n)))
      (graph-edges g)))))

;; sygnatura dla struktury danych
(define-signature bag^
  ((contracted
    [bag?       (-> any/c boolean?)]
    [empty-bag  (and/c bag? bag-empty?)]
    [bag-empty? (-> bag? boolean?)]
    [bag-insert (-> bag? any/c (and/c bag? (not/c bag-empty?)))]
    [bag-peek   (-> (and/c bag? (not/c bag-empty?)) any/c)]
    [bag-remove (-> (and/c bag? (not/c bag-empty?)) bag?)])))

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag? b)
    (or (list? b)
        (bag-empty? b)))

  (define (bag-empty? b)
    (eq? b 'empty-stack))
  
  (define empty-bag 'empty-stack)

  (define (bag-insert b v)
    (if (bag-empty? b)
        (list v)
        (cons v b)))

  (define (bag-peek b)
    (first b))

  (define (bag-remove b)
    (if (= (length b) 1)
        empty-bag        
        (cdr b)))
    

;; TODO: zaimplementuj stos
)

;; struktura danych - kolejka FIFO
;; do zaimplementowania przez studentów
(define-unit bag-fifo@
  (import)
  (export bag^)

  (define (queue-in b)
    (first b))

  (define (queue-out b)
    (second b))

  (define (make-bag b)
    (if (null? (queue-out b))
        (list '() (reverse (queue-in b)))
        b))

  (define (bag? b)
    (and (pair? b)
         (= (length b) 2)
         (list? (queue-in b))
         (list? (queue-out b))))

  (define (bag-empty? b)
    (and (null? (queue-in b))
         (null? (queue-out b))))

  (define empty-bag '(() ()))

  (define (bag-insert b v)
    (if (null? (queue-out b))
        (list '() (reverse (cons v (queue-in b))))
        (list (cons v (queue-in b)) (queue-out b))))


  (define (bag-peek b)
    (first (queue-out b)))

  (define (bag-remove b)
    (if (null? (queue-out b))
        (list '() (cdr (reverse (queue-in b))))
        (make-bag (list (queue-in b) (cdr (queue-out b))))))         

)

;; sygnatura dla przeszukiwania grafu
(define-signature graph-search^
  (search))

;; implementacja przeszukiwania grafu
;; uzależniona od implementacji grafu i struktury danych
(define-unit/contract graph-search@
  (import bag^ graph^)
  (export (graph-search^
           [search (-> graph? any/c (listof any/c))]))
  (define (search g n)
    (define (it g b l)
      (cond
        [(bag-empty? b) (reverse l)]
        [(has-node? g (bag-peek b))
         (it (remove-node g (bag-peek b))
             (foldl
              (lambda (n1 b1) (bag-insert b1 n1))
              (bag-remove b)
              (outnodes g (bag-peek b)))
             (cons (bag-peek b) l))]
        [else (it g (bag-remove b) l)]))
    (it g (bag-insert empty-bag n) '()))
  )

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))

;; TODO: napisz inne testowe grafy!

(define graph1
  (graph
   (list 1 2 3 4)
   (list (edge 1 2)
         (edge 1 3)
         (edge 1 4)
         (edge 2 3)
         (edge 2 4)
         (edge 3 4))))

(define graph2
  (graph
   (list 1 2 3 4 5 6)
   (list (edge 1 2)
         (edge 1 3)
         (edge 1 5)
         (edge 3 4)
         (edge 4 5)
         (edge 5 6))))

(define graph3
  (graph
   (list 1 2 3 4 5 6)
   (list (edge 1 2)
         (edge 1 3)
         (edge 1 6)
         (edge 2 4)
         (edge 3 5)
         (edge 3 4)
         (edge 5 6))))

(define graph4
  (graph
   (list 1 2 3 4 5 6 7)
   (list (edge 1 2)
         (edge 2 3)
         (edge 2 4)
         (edge 4 5)
         (edge 4 6)
         (edge 6 7))))

(define graph5
  (graph
   (list 1 2 3 4 5 6 7)
   (list (edge 1 2)
         (edge 1 6)
         (edge 2 7)
         (edge 2 3)
         (edge 3 4)
         (edge 3 7)
         (edge 4 5)
         (edge 5 7)
         (edge 5 6)
         (edge 6 7))))

(define graph6
  (graph
   (list 1 2 3 4 5 6 7)
   (list (edge 1 2)
         (edge 1 7)
         (edge 2 7)
         (edge 2 3)
         (edge 2 4)
         (edge 3 4)
         (edge 4 5)
         (edge 4 7)
         (edge 4 6)
         (edge 5 6)
         (edge 6 7))))

;; otwarcie komponentu stosu
 (define-values/invoke-unit/infer bag-stack@)
;; opcja 2: otwarcie komponentu kolejki
; (define-values/invoke-unit/infer bag-fifo@)

;; testy w Quickchecku
(require quickcheck)

;; test przykładowy: jeśli do pustej struktury dodamy element
;; i od razu go usuniemy, wynikowa struktura jest pusta
(quickcheck
 (property ([s arbitrary-symbol])
           (bag-empty? (bag-remove (bag-insert empty-bag s)))))
;; TODO: napisz inne własności do sprawdzenia!
;; jeśli jakaś własność dotyczy tylko stosu lub tylko kolejki,
;; wykomentuj ją i opisz to w komentarzu powyżej własności


;; Testy wspólne

(quickcheck
 (property ([s arbitrary-symbol])
           (eq? s (bag-peek (bag-insert empty-bag s)))))

(quickcheck
 (property ([a arbitrary-symbol]
            [b arbitrary-symbol]
            [c arbitrary-symbol]
            [d arbitrary-symbol]
            [e arbitrary-symbol]
            [f arbitrary-symbol])
           (bag-empty?
            (bag-remove
             (bag-remove
              (bag-remove
               (bag-remove
                (bag-remove
                 (bag-remove
                  (bag-insert
                   (bag-insert (bag-insert (bag-insert (bag-insert (bag-insert empty-bag a) b) c) d) e) f))))))))))

(quickcheck
 (property ([a arbitrary-symbol]
            [b arbitrary-symbol]
            [c arbitrary-symbol]
            [d arbitrary-symbol]
            [e arbitrary-symbol]
            [f arbitrary-symbol])
           (bag?
               (bag-remove
                (bag-remove
                 (bag-remove
                  (bag-insert
                   (bag-insert (bag-insert (bag-insert (bag-insert (bag-insert empty-bag a) b) c) d) e) f)))))))


;; Testy dla stosu

(quickcheck
 (property ([s arbitrary-symbol]
            [p arbitrary-symbol])
           (eq? p (bag-peek (bag-insert (bag-insert empty-bag s) p)))))

(quickcheck
 (property ([s arbitrary-symbol]
            [p arbitrary-symbol])
           (eq? s (bag-peek (bag-remove (bag-insert (bag-insert empty-bag s) p))))))

(quickcheck
 (property ([a arbitrary-symbol]
            [b arbitrary-symbol]
            [c arbitrary-symbol]
            [d arbitrary-symbol]
            [e arbitrary-symbol]
            [f arbitrary-symbol])
           (eq? c
                (bag-peek
                 (bag-remove
                  (bag-remove
                   (bag-remove
                    (bag-insert
                     (bag-insert (bag-insert (bag-insert (bag-insert (bag-insert empty-bag a) b) c) d) e) f))))))))



;; Testy dla kolejki

(quickcheck
 (property ([s arbitrary-symbol]
            [p arbitrary-symbol])
           (eq? s (bag-peek (bag-insert (bag-insert empty-bag s) p)))))

(quickcheck
 (property ([s arbitrary-symbol]
            [p arbitrary-symbol])
           (eq? p (bag-peek (bag-remove (bag-insert (bag-insert empty-bag s) p))))))

(quickcheck
 (property ([a arbitrary-symbol]
            [b arbitrary-symbol]
            [c arbitrary-symbol]
            [d arbitrary-symbol]
            [e arbitrary-symbol]
            [f arbitrary-symbol])
           (eq? d
                (bag-peek
                 (bag-remove
                  (bag-remove
                   (bag-remove
                    (bag-insert
                     (bag-insert (bag-insert (bag-insert (bag-insert (bag-insert empty-bag a) b) c) d) e) f))))))))

;; otwarcie komponentu przeszukiwania
(define-values/invoke-unit/infer graph-search@)

;; uruchomienie przeszukiwania na przykładowym grafie
(search test-graph 1)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach!

(search graph1 1)
(search graph2 1)
(search graph3 1)
(search graph4 1)
(search graph5 1)
(search graph6 1)