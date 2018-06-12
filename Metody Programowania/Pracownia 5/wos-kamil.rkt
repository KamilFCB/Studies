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

;; reprezentacja danych wejściowych (z ćwiczeń)
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

;; przydatne predykaty na zmiennych
(define (var<? x y)
  (symbol<? x y))

(define (var=? x y)
  (eq? x y))

(define (literal? x)
  (and (tagged-tuple? 'literal 3 x)
       (boolean? (cadr x))
       (var? (caddr x))))

(define (literal pol x)
  (list 'literal pol x))

(define (literal-pol x)
  (cadr x))

(define (literal-var x)
  (caddr x))

(define (clause? x)
  (and (tagged-list? 'clause x)
       (andmap literal? (cdr x))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? x)
  (and (tagged-list? 'cnf x)
       (andmap clause? (cdr x))))

(define (cnf . cs)
    (cons 'cnf cs))

(define (cnf-clauses x)
  (cdr x))

;; oblicza wartość formuły w CNF z częściowym wartościowaniem. jeśli zmienna nie jest
;; zwartościowana, literał jest uznawany za fałszywy.
(define (valuate-partial val form)
  (define (val-lit l)
    (let ((r (assoc (literal-var l) val)))
      (cond
       [(not r)  false]
       [(cadr r) (literal-pol l)]
       [else     (not (literal-pol l))])))
  (define (val-clause c)
    (ormap val-lit (clause-lits c)))
  (andmap val-clause (cnf-clauses form)))

;; reprezentacja dowodów sprzeczności

(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (proof-axiom c)
  (list 'axiom c))

(define (axiom-clause p)
  (cadr p))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (proof-res x pp pn)
  (list 'resolve x pp pn))

(define (res-var p)
  (cadr p))

(define (res-proof-pos p)
  (caddr p))

(define (res-proof-neg p)
  (cadddr p))

;; sprawdza strukturę, ale nie poprawność dowodu
(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;; procedura sprawdzająca poprawność dowodu
(define (check-proof pf form)
  (define (run-axiom c)
    (displayln (list 'checking 'axiom c))
    (and (member c (cnf-clauses form))
         (clause-lits c)))
  (define (run-res x cpos cneg)
    (displayln (list 'checking 'resolution 'of x 'for cpos 'and cneg))
    (and (findf (lambda (l) (and (literal-pol l)
                                 (eq? x (literal-var l))))
                cpos)
         (findf (lambda (l) (and (not (literal-pol l))
                                 (eq? x (literal-var l))))
                cneg)
         (append (remove* (list (literal true x))  cpos)
                 (remove* (list (literal false x)) cneg))))
  (define (run-proof pf)
    (cond
     [(axiom? pf) (run-axiom (axiom-clause pf))]
     [(res? pf)   (run-res (res-var pf)
                           (run-proof (res-proof-pos pf))
                           (run-proof (res-proof-neg pf)))]
     [else        false]))
  (null? (run-proof pf)))


;; reprezentacja wewnętrzna

;; sprawdza posortowanie w porządku ściśle rosnącym, bez duplikatów
(define (sorted? vs)
  (or (null? vs)
      (null? (cdr vs))
      (and (var<? (car vs) (cadr vs))
           (sorted? (cdr vs)))))

(define (sorted-varlist? x)
  (and (list? x)
       (andmap (var? x))
       (sorted? x)))

;; klauzulę reprezentujemy jako parę list — osobno wystąpienia pozytywne i negatywne. Dodatkowo
;; pamiętamy wyprowadzenie tej klauzuli (dowód) i jej rozmiar.
(define (res-clause? x)
  (and (tagged-tuple? 'res-int 5 x)
       (sorted-varlist? (second x))
       (sorted-varlist? (third x))
       (= (fourth x) (+ (length (second x)) (length (third x))))
       (proof? (fifth x))))

(define (res-clause pos neg proof)
  (list 'res-int pos neg (+ (length pos) (length neg)) proof))

(define (res-clause-pos c)
  (second c))

(define (res-clause-neg c)
  (third c))

(define (res-clause-size c)
  (fourth c))

(define (res-clause-proof c)
  (fifth c))

;; przedstawia klauzulę jako parę list zmiennych występujących odpowiednio pozytywnie i negatywnie
(define (print-res-clause c)
  (list (res-clause-pos c) (res-clause-neg c)))

;; sprawdzanie klauzuli sprzecznej
(define (clause-false? c)
  (and (null? (res-clause-pos c))
       (null? (res-clause-neg c))))

;; pomocnicze procedury: scalanie i usuwanie duplikatów z list posortowanych
(define (merge-vars xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [(var<? (car xs) (car ys))
         (cons (car xs) (merge-vars (cdr xs) ys))]
        [(var<? (car ys) (car xs))
         (cons (car ys) (merge-vars xs (cdr ys)))]
        [else (cons (car xs) (merge-vars (cdr xs) (cdr ys)))]))

(define (remove-duplicates-vars xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [(var=? (car xs) (cadr xs)) (remove-duplicates-vars (cdr xs))]
        [else (cons (car xs) (remove-duplicates-vars (cdr xs)))]))

(define (rev-append xs ys)
  (if (null? xs) ys
      (rev-append (cdr xs) (cons (car xs) ys))))

;; TODO: miejsce na uzupełnienie własnych funkcji pomocniczych

(define (clause-trivial? c)
  (intersection-not-empty? (res-clause-pos c) (res-clause-neg c)))
        
(define (intersection-not-empty? pos-vars neg-vars)
  (cond [(null? pos-vars) false]
        [(null? neg-vars) false]
        [(member (car pos-vars) neg-vars) true]
        [else (intersection-not-empty? (cdr pos-vars) neg-vars)]))

(define (find-var pos-vars neg-vars)
  (if (member (car pos-vars) neg-vars)
      (car pos-vars)
      (find-var (cdr pos-vars) neg-vars)))

(define (resolve c1 c2)
  (if (or (clause-trivial? c1) (clause-trivial? c2))
      false
      (let* ([c1-neg-vars (res-clause-neg c1)]
             [c1-pos-vars (res-clause-pos c1)]
             [c2-neg-vars (res-clause-neg c2)]
             [c2-pos-vars (res-clause-pos c2)]
             [new-pos-vars (remove-duplicates-vars (merge-vars c1-pos-vars c2-pos-vars))]
             [new-neg-vars (remove-duplicates-vars (merge-vars c1-neg-vars c2-neg-vars))])
        (if (intersection-not-empty? new-pos-vars new-neg-vars)
            (let* ([var (find-var new-pos-vars new-neg-vars)]
                   [res-pos-vars (remove var new-pos-vars)]
                   [res-neg-vars (remove var new-neg-vars)])
              (if (member var c1-pos-vars)
                  (res-clause res-pos-vars res-neg-vars (proof-res var (res-clause-proof c1) (res-clause-proof c2)))
                  (res-clause res-pos-vars res-neg-vars (proof-res var (res-clause-proof c2) (res-clause-proof c1)))))
            false))))

(define (resolve-single-prove s-clause checked pending)
  ;; TODO: zaimplementuj!
  ;; Poniższa implementacja działa w ten sam sposób co dla większych klauzul — łatwo ją poprawić!
  (let* ((resolvents   (filter-map (lambda (c) (resolve c s-clause))
                                   checked))
         (sorted-rs    (sort resolvents < #:key res-clause-size))
         (pending-resolvents (filter-map (lambda (c) (resolve c s-clause))
                                         pending))
         (sorted-pending (sort-clauses pending-resolvents)))
    (cond [(or (null? sorted-rs)
               (null? sorted-pending))
           (subsume-add-prove (cons s-clause checked) pending sorted-rs)]
          [( = (res-clause-size (car sorted-rs)) 0)
           (list 'unsat (res-clause-proof (car sorted-rs)))]
          [(and (not (null? (car sorted-pending)))
                (= (res-clause-size (car sorted-pending)) 0))
           (list 'unsat (res-clause-proof (car sorted-pending)))]
          [else (resolve-prove (cons s-clause sorted-rs) pending)])))

;; wstawianie klauzuli w posortowaną względem rozmiaru listę klauzul
(define (insert nc ncs)
  (cond
   [(null? ncs)                     (list nc)]
   [(< (res-clause-size nc)
       (res-clause-size (car ncs))) (cons nc ncs)]
   [else                            (cons (car ncs) (insert nc (cdr ncs)))]))

;; sortowanie klauzul względem rozmiaru (funkcja biblioteczna sort)
(define (sort-clauses cs)
  (sort cs < #:key res-clause-size))

;; główna procedura szukająca dowodu sprzeczności
;; zakładamy że w checked i pending nigdy nie ma klauzuli sprzecznej
(define (resolve-prove checked pending)
  (cond
   ;; jeśli lista pending jest pusta, to checked jest zamknięta na rezolucję czyli spełnialna
   [(null? pending) (generate-valuation (sort-clauses checked))]
   ;; jeśli klauzula ma jeden literał, to możemy traktować łatwo i efektywnie ją przetworzyć
   [(= 1 (res-clause-size (car pending)))
    (resolve-single-prove (car pending) checked (cdr pending))]
   ;; w przeciwnym wypadku wykonujemy rezolucję z wszystkimi klauzulami już sprawdzonymi, a
   ;; następnie dodajemy otrzymane klauzule do zbioru i kontynuujemy obliczenia
   [else
    (let* ((next-clause  (car pending))
           (rest-pending (cdr pending))
           (resolvents   (filter-map (lambda (c) (resolve c next-clause))
                                     checked))
           (sorted-rs    (sort-clauses resolvents)))
      (subsume-add-prove (cons next-clause checked) rest-pending sorted-rs))]))

;; procedura upraszczająca stan obliczeń biorąc pod uwagę świeżo wygenerowane klauzule i
;; kontynuująca obliczenia. Do uzupełnienia.
(define (subsume-add-prove checked pending new)
  (cond
   [(null? new)                 (resolve-prove checked pending)]
   ;; jeśli klauzula do przetworzenia jest sprzeczna to jej wyprowadzenie jest dowodem sprzeczności
   ;; początkowej formuły
   [(clause-false? (car new))   (list 'unsat (res-clause-proof (car new)))]
   ;; jeśli klauzula jest trywialna to nie ma potrzeby jej przetwarzać
   [(clause-trivial? (car new)) (subsume-add-prove checked pending (cdr new))]
   [else
    ;; TODO: zaimplementuj!
    ;; Poniższa implementacja nie sprawdza czy nowa klauzula nie jest lepsza (bądź gorsza) od już
    ;; rozpatrzonych; popraw to!
    (if (easier-exist? (car new) (append checked pending))
        (subsume-add-prove checked pending (cdr new))
        (let ([new-checked (delete-easier (car new) checked)]
              [new-pending (delete-easier (car new) pending)])
          (subsume-add-prove new-checked (insert (car new) new-pending) (cdr new))))
    ]))

(define (delete-easier easy cl)
  (define (iter cl acc)
    (cond [(null? cl) acc]
          [(easier? easy (car cl)) (iter (cdr cl) acc)]
          [else (iter (cdr cl) (cons (car cl) acc))]))
  (iter cl null))

(define (easier-exist? easy cl)
  (cond [(null? cl) #f]
        [(easier? (car cl) easy) #t]
        [else (easier-exist? easy (cdr cl))]))

(define (easier? c1 c2)
  (define (iter c1-pos c1-neg c2-pos c2-neg)
    (cond
      [(and
        (null? c1-pos)
        (null? c1-neg)) #t]
      [(null? c1-pos)
       (and (member (car c1-neg) c2-neg)
            (iter c1-pos (cdr c1-neg) c2-pos c2-neg))]
      [(null? c1-neg)
       (and (member (car c1-pos) c2-pos)
            (iter (cdr c1-pos) c1-neg c2-pos c2-neg))]
      [else (and
             (member (car c1-neg) c2-neg)
             (member (car c1-pos) c2-pos)
             (iter (cdr c1-pos) (cdr c1-neg) c2-pos c2-neg))]))
  (iter (res-clause-pos c1) (res-clause-neg c1) (res-clause-pos c2) (res-clause-neg c2)))

(define (generate-valuation resolved)
  ;; TODO: zaimplementuj!
  ;; Ta implementacja mówi tylko że formuła może być spełniona, ale nie mówi jak. Uzupełnij ją!  
  (define (clear var l)
    (if (null? l)
        null
        (let* ([curr (car l)]
               [new-pos (remove var (res-clause-pos curr))]
               [new-neg (remove var (res-clause-neg curr))])
          (if (and
               (null? new-pos)
               (null? new-neg))
              (clear var (cdr l))
              (cons (res-clause new-pos new-neg (res-clause-proof curr))
                    (clear var (cdr l)))))))            
  (define (iter resolved evaluation)
    (if (null? resolved)
        evaluation
        (let ([curr (car resolved)])
             (cond [(not (null? (res-clause-neg curr)))
                    (iter (clear (car (res-clause-neg curr)) (cdr resolved))
                          (cons (list (car (res-clause-neg curr)) '#f) evaluation))]
                   [(not (null? (res-clause-pos curr)))
                    (iter (clear (car (res-clause-pos curr)) (cdr resolved))
                          (cons (list (car (res-clause-pos curr)) '#t) evaluation))]
                   [else (iter (cdr resolved) evaluation)]))))
  (list 'sat (iter resolved null)))

;; procedura przetwarzające wejściowy CNF na wewnętrzną reprezentację klauzul
(define (form->clauses f)
  (define (conv-clause c)
    (define (aux ls pos neg)
      (cond
       [(null? ls)
        (res-clause (remove-duplicates-vars (sort pos var<?))
                    (remove-duplicates-vars (sort neg var<?))
                    (proof-axiom c))]
       [(literal-pol (car ls))
        (aux (cdr ls)
             (cons (literal-var (car ls)) pos)
             neg)]
       [else
        (aux (cdr ls)
             pos
             (cons (literal-var (car ls)) neg))]))
    (aux (clause-lits c) null null))
  (map conv-clause (cnf-clauses f)))

(define (prove form)
  (let* ((clauses (form->clauses form)))
    (subsume-add-prove '() '() clauses)))

;; procedura testująca: próbuje dowieść sprzeczność formuły i sprawdza czy wygenerowany
;; dowód/waluacja są poprawne. Uwaga: żeby działała dla formuł spełnialnych trzeba umieć wygenerować
;; poprawną waluację.
(define (prove-and-check form)
  (let* ((res (prove form))
         (sat (car res))
         (pf-val (cadr res)))
    (if (eq? sat 'sat)
        (valuate-partial pf-val form)
        (check-proof pf-val form))))

;;; TODO: poniżej wpisz swoje testy

(define c1 '(clause (literal #f p) (literal #t q)))
(define c2 '(clause (literal #t p) (literal #f q)))
(define cnf1 (cons 'cnf (list c1 c2))) 
(prove-and-check cnf1)

(define c3 '(clause (literal #t p) (literal #t q) (literal #t r)))
(define c4 '(clause (literal #t p) (literal #f q) (literal #f r)))
(define c5 '(clause (literal #f q) (literal #t r)))
(define c6 '(clause (literal #f r) (literal #t p)))
(define cnf2 (cons 'cnf (list c3 c4 c5 c6)))
(prove-and-check (cons 'cnf (list c3 c4 c5 c6)))

(define c7 '(clause (literal #t p) (literal #t r)))
(define c8 '(clause (literal #t q) (literal #t s)))
(define c9 '(clause (literal #f p) (literal #f q)))
(define cnf3 (cons 'cnf (cons 'cnf (list c7 c8 c9))))
(prove-and-check (cons 'cnf (list c7 c8 c9)))

(define c10 '(clause (literal #t p) (literal #t r)))
(define c11 '(clause (literal #f r) (literal #f s)))
(define c12 '(clause (literal #t q) (literal #t s)))
(define c13 '(clause (literal #t q) (literal #t r)))
(define c14 '(clause (literal #f p) (literal #f q)))
(define c15 '(clause (literal #t p) (literal #t s)))
(define cnf4 (cons 'cnf (list c10 c11 c12 c13 c14 c15)))
(prove-and-check cnf4)

(define c16 '(clause (literal #t p) (literal #t q) (literal #t r)))
(define c17 '(clause (literal #f p) (literal #f q) (literal #f r)))
(define c18 '(clause (literal #f q) (literal #t r)))
(define c19 '(clause (literal #t p) (literal #f r)))
(define cnf5 (cons 'cnf (list c10 c11 c12 c13 c14 c15)))
(prove-and-check cnf5)

(define c20 '(clause (literal #f p) (literal #t q)))
(define c21 '(clause (literal #f p) (literal #f r) (literal #t s)))
(define c22 '(clause (literal #f q) (literal #t r)))
(define c23 '(clause (literal #t p)))
(define c24 '(clause (literal #f s)))
(define cnf6 (cons 'cnf (list c20 c21 c22 c23 c24)))
(prove-and-check cnf6)