#lang scheme
(define ( divisible? dividend divisor)
  (equal? (remainder dividend divisor) 0))
;############### Problem 1 ###############
(define (prob1 maxNum)
  (let ((sum 0))
    (let loop ((num 0))
      (if (= num maxNum) sum
          (begin
            (cond
              ((divisible? num 3) (set! sum (+ sum num)))
              ((divisible? num 5) (set! sum (+ sum num))))
            (loop (+ num 1)))))))

  
                   
                   
                     
                
                  
                      
              
    

              