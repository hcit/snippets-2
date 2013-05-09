(defun pythagorean-triplet-prob ()                                    
           (do ((b 2 (1+ b)))                                                   
               ((= b 1000))                                                     
             (loop for a below b                                                
                  do                                                            
                  (when(= (+ (expt a 2) (expt b 2)) (expt (- 1000 (+ a b)) 2))  
                    (format t "~a ~a " a b )                  
                    (return)))))
