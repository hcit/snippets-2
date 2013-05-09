;; Implementation of a simple variant of  RLE
;; By Thura Hlaing <trhura@gmail.com>

;; Algorithm
;; Whenever a character is repeated (appears 2 times), we put a number after it
;; which inidicate how many more times it is repeated.
;; For instance, "wwwwwwwwbb3333333123" will be decoded into"ww6bb0335123"

(defun rle-encode (string)
  (loop as prev-char = #\Null then char
     for char in (coerce string 'list) 
     with repeat-times = 0 and stream = (make-string-output-stream)
     if (and (char= prev-char char) (<= repeat-times 9)) do
       (incf repeat-times)
     else if (> repeat-times 0) do
       (format stream "~a~a~a" prev-char (1- repeat-times) char)
       (setf repeat-times 0)
     else do
       (format stream "~a" char)
     finally (return (get-output-stream-string stream))))

(defun rle-decode (string)
  (loop for char in (coerce string 'list)
     with prev-char = #\Null and repeated = nil and
     stream = (make-string-output-stream)
     if repeated do
       (let* ((repeated-times (parse-integer (string char)))
	      (format-string (format nil "~~0,0,~a,'~a@a" repeated-times prev-char)))
	 (format stream "~@?" format-string  prev-char)
	 (setf repeated nil prev-char #\Null))
     else if (char= prev-char char) do
       (setf repeated T)
     else do
       (format stream "~a" char)
       (setf prev-char char) 
     finally (return (get-output-stream-string stream))))

       
;;Testing
(let* ((string "wwwwwwwwbb3333333123")
       (encoded-string (rle-encode string))
       (decoded-string (rle-decode encoded-string)))
  (format t "original string = ~a ~%" string)
  (format t "encoded string = ~a ~%" encoded-string)
  (format t "decoded string = ~a ~%" decoded-string))
