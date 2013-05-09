(defun prob5 (start end)
 (let ((start-time (get-universal-time)))
  (do ((tmp (* 2 end) (+ tmp end)))
      (())
     (loop for i from start to end
	   do
	   (cond ((not (zerop (rem tmp i)))
		  (return))
		 ((= i end)
		  (format t "Ans --> ~a Elapsed Time -->~a ~%"
			  tmp
			  (- (get-universal-time) start-time))
		  (return-from prob5)))))))
