;; Implementation of static minimum variance huffman algorithm
;; By Thura Hlaing <trhura@gmail.com> 


(defun hf-get-symbol-table (string &key (for 'encode))
  ;; Get the symbol table :for can be either encode or decode
  ;; For encode, the hashtable will use the symobls as keys
  ;; For decode, the hashtable will use the prefix codes as keys
  (labels ((sort-func (x y) (< (cdr x) (cdr y)))
	   (build-tree (list)
	     (if (<= (length list) 2)
		 (cons (caar list) (caadr list))
		 (let* ((first-item  (first list))
			(second-item (second list))
			(new-node (cons (cons (car first-item)
					      (car second-item))
					(+ (cdr first-item)
					   (cdr second-item)))))
		   (setf list (delete first-item list :test #'equal)
			 list (delete second-item list :test #'equal))
		   (nconc list (list new-node))
		   (build-tree (sort list #'sort-func)))))
	   (build-table (tree &optional (prefix nil)
			       (hashtable (make-hash-table :test 'equal)))
	     (if (characterp tree)
		 (if (eql for 'encode)
		     (setf (gethash tree hashtable)
			   prefix)
		     (setf (gethash prefix hashtable)
			   tree))
		 (progn
		   (build-table (car tree)
				(concatenate 'string prefix "0")
				hashtable)
		   (build-table (cdr tree)
				(concatenate 'string prefix "1")
				hashtable)
		   hashtable))))
    (let* ((list (coerce string 'list))
	   (unique-list (remove-duplicates list))
	   (list-with-freq (loop for item in unique-list
			      collecting (cons item 
					       (count item list))))
	   (sorted-list (sort list-with-freq #'sort-func)))
      (build-table (build-tree sorted-list)))))

(defun hf-print-table (string)
  (let ((table (hf-get-symbol-table string)))
    (format t "~%~10a ~10a ~10a~%" "Symbol" "Frequency" "Code")
    (loop for key being each hash-key of table
       do (format t "~10a ~10a ~10a~%" key (count key string) (gethash key table)))))

(defun hf-encode (string &key (destination *standard-output*))
  ;; encode the given string, return a symbol table for decoding
  (loop
     with hashtable = (hf-get-symbol-table string)
     for ch in (coerce string 'list)
     do (format destination "~a" (gethash ch hashtable))
     finally (return (hf-get-symbol-table string :for 'decode))))

(defun hf-decode (string hashtable &key (destination *standard-output*))
  ;; decode the given string, according to symbol table
  (loop with start = 0 
     as end = 1 then (1+ end)
     do (let ((hash-value (gethash (subseq string start end) hashtable)))
	  (if hash-value 
	      (progn
		(format destination "~a" hash-value) 
		(setf start end)))) 
     while (< end (length string)))) 

;; Testing
(let* ((string "aaaaaaaaaaaaaaabbbbbbbccccccddddddeeeee")
       (stream (make-string-output-stream))
       (table  (hf-encode string :destination stream))
       (encoded-string (get-output-stream-string stream))) 

  (format t "original string = ~a~%" string)
  (hf-print-table string)
  (format t "~%encoded string = ~a~%" encoded-string)
  
  (hf-decode encoded-string table :destination stream) 
  (format t "decoded string = ~a~%"   (get-output-stream-string stream)))