(defun get-nth-prime (n)                                               
                (let  ((count 1))                                               
                  (do ((i 3 (+ i 2)))                                           
                      (())                                                      
                    (when((lambda (x)                                           
                          (loop for factor from 2 to (isqrt x) 
                               never (zerop (mod x factor)))) i)                
                      (setf count (1+ count))                                   
                      (if(= count n)                                            
                         (return i))))))


