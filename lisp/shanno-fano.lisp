;; Implementation of static shanno-fano algorithm
;; By Thura Hlaing <trhura@gmail.com>

;; Algorithm - (Taken from Wikipedia)

;; 1.	For a given list of symbols, develop a corresponding list of probabilities
;;	or frequency counts so that each symbol’s relative frequency of occurrence is known.
;; 2.	Sort the lists of symbols according to frequency, with the most frequently
;;	occurring symbols at the left and the least common at the right.
;; 3.	Divide the list into two parts, with the total frequency counts of the left half
;;	being as close to the total of the right as possible.
;; 4.	The left half of the list is assigned the binary digit 0, and
;;	the right half is assigned the digit 1. This means that the codes for the symbols in the
;;	first half will all start with 0, and the codes in the second half will all start with 1.
;; 5.	Recursively apply the steps 3 and 4 to each of the two halves, subdividing groups and
;;	adding bits to the codes until each symbol has become a corresponding code leaf on the tree.

(defun get-divide-pos (sorted-list)
  ;; Get the position to divide the list into two parts (See step 3)
  (labels ((divide-pos (list pos)
	     (let* ((bfc (loop for x from 0 to (1- pos)
			    summing (cdr (elt list x))))
		    (afc (loop for x from (1+ pos) to (1- (length list))
			    summing (cdr (elt list x))))
		    (cfc (cdr (elt list pos))))
	       (if (>= (+ afc cfc) bfc)
		   (if (< bfc afc)
		       (1+ pos)
		       pos)
		   (divide-pos list (1- pos))))))
    (divide-pos sorted-list (floor (/ (length sorted-list) 2)))))

(defun sf-get-symbol-table (string &key (for 'encode))
  ;; Get the symbol table :for can be either encode or decode
  ;; For encode, the hashtable will use the symobls as keys
  ;; For decode, the hashtable will use the prefix codes as keys
  (labels ((build-table (list &optional (prefix nil)
			       (hashtable (make-hash-table :test 'equal)))
	     (if (null (rest list))
		 ;; if the list of pairs has left only one pair, step 4
		 (if (eql for 'encode)
		     (setf (gethash (car (first list)) hashtable) 
			   prefix)
		     (setf (gethash prefix hashtable)
			   (car (first list))))
		 ;; else (step 5) divide the list into lhs and rhs, assign 0 and respectively
		 ;; recursively apply step 3 and 4 
		 (let* ((pivot (get-divide-pos list))) 
		   (build-table (subseq list 0 pivot)
				(concatenate 'string prefix "0")
				hashtable)
		   (build-table (subseq list pivot)
				(concatenate 'string prefix "1")
				hashtable)
		   ;; finally return the hashtable
		   hashtable)))) 
    (let* ((list (coerce string 'list)) ; convert the string into a list of chars (symbol)
	   ;; remove reoccuring symbols
	   (unique-list (remove-duplicates list))
	   ;; make a list of pairs in the form (symobol . frequency)
	   (list-with-freq (loop for item in unique-list
			      collecting (cons item
					       (count item list))))
	   ;; sort the list based on the frequency
	   (sorted-list (sort list-with-freq
			      (lambda (x y) (> (cdr x) (cdr y))))))
      ;; build hash table
      (build-table sorted-list))))

(defun sf-encode (string &key (destination *standard-output*))
  ;; encode the given string, return a symbol table for decoding
  (loop
     with hashtable = (sf-get-symbol-table string)
     for ch in (coerce string 'list)
     do (format destination "~a" (gethash ch hashtable))
     finally (return (sf-get-symbol-table string :for 'decode))))

(defun sf-decode (string hashtable &key (destination *standard-output*))
  ;; decode the given string, according to symbol table
  (loop with start = 0 
     as end = 1 then (1+ end)
     do (let ((hash-value (gethash (subseq string start end) hashtable)))
	  (if hash-value 
	      (progn
		(format destination "~a" hash-value) 
		(setf start end)))) 
     while (< end (length string))))

(defun sf-print-table (string)
  (let ((table (sf-get-symbol-table string)))
    (format t "~%~10a ~10a ~10a~%" "Symbol" "Frequency" "Code")
    (loop for key being each hash-key of table
       do (format t "~10a ~10a ~10a~%" key (count key string) (gethash key table)))))

;; Testing
(let* ((string "aaaaaaaaaaaaaaabbbbbbbccccccddddddeeeee")
       (stream (make-string-output-stream))
       (table  (sf-encode string :destination stream))
       (encoded-string (get-output-stream-string stream))) 

  (format t "original string = ~a~%" string)
  (sf-print-table string)
  (format t "~%encoded string = ~a~%" encoded-string)
  
  (sf-decode encoded-string table :destination stream) 
  (format t "decoded string = ~a~%"   (get-output-stream-string stream)))