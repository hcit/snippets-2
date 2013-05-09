(defun sum-of-primes (below)                                           
           (let ((sum 0))                                                       
             (do ((i 2 (1+ i)))                                                 
                 ((= i below))                                                  
               (if((lambda (x)                                                  
                    (loop for factor from 2 to (isqrt x) never (zerop (mod x factor)))) i)                                                                     
                  (setf sum (+ sum i))))                                        
             (return-from sum-of-primes sum)))
(format t "~a" (sum-of-primes 1000))