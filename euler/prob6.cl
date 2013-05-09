(defun prob5 (num)
  (let ((sum1 0)
	(sum2 0))
    (loop for x from 1 to num do
	  (setf sum1 (+ sum1 (* x x)))
	  (setf sum2 (+ sum2 x)))	  
    (setf sum2 (* sum2 sum2))
    (- sum2 sum1)))

