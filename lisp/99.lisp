(defun my-but-last (list)
  (if (null (cddr list))
	  list
	  (my-but-last (cdr list))))

(defun my-last (list)
  (if(null (cdr list))
	 list
	 (my-last (cdr list))))

(defun element-at (list pos)
  (if (= 1 pos)
	  (car list)
	  (element-at (cdr list) (1- pos))))

(defun my-length (list)
  (labels ((rec (list len)
			 (if (null (cdr list))
				 (1+ len)
				 (rec (cdr list) (1+ len)))))
	(rec list 0)))

(defun my-reverse (list)
  (labels ((rec (list acc)
			 (if (null lst)
				 acc
				 (rec (my-but-last