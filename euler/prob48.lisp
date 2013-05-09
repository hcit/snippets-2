(defun prob48 (n)
  (labels ((recur (i acc)
			 (if (> i n)
				 acc
				 (recur (1+ i) (rem (+ acc (expt i i)) 10000000000)))))
	(recur 1 0)))

(defun prob48-2 (n)
  (labels ((recur (i acc)
			 (if (> i n)
				 (rem acc 10000000000)
				 (recur (1+ i) (+ acc (expt i i))))))
	(recur 1 0)))




