#lang scheme
(define ( divisible? dividend divisor)
  (equal? (remainder dividend divisor) 0))
;############### Problem 2 ###############
(define (prob2 maxNum)
  (let ((sum 0))
    (let loop ((x 1)
               (y 2))
      (if (> y maxNum) sum
      (begin
        (when (divisible? y 2) (set! sum (+ sum y)))
        (set! y (+ x y))
        (set! x (- y x))
        (loop x y))))))
       
       
             
             
             
       
    