
#lang scheme/gui

(define new-game #t)
(define game-finished #f)

(define user-move #\X)
(define computer-move #\O)
(define move-count 0)

(define start-move user-move)
(define current-move start-move)

(define main-board (make-vector 9 #\space))
(define win-paths '((0 1 2) (0 3 6) (0 4 8) (3 4 5) (1 4 7) (2 4 6) (6 7 8) (2 5 8)))
(define win-move '(0 0 0))

(define (prepare-new-game)
  ;; Reset Data for a new game
  (let ((user-first (send start-menu is-checked?)))
    ;; set start move according to menu
    (if user-first
        (set! start-move user-move)
        (set! start-move computer-move))

    ;; reset board and other data
    (set! main-board (make-vector 9 #\Space))
    (set! current-move start-move)
    (set! game-finished #f)
    (set! move-count 0)
    (set! new-game #f) 
   
    ;; Reset Canvases
    (for [(canvas  canvases)]
      (send canvas set-character #\Space)
      (send canvas set-color (make-object color% "gray"))
      (send canvas refresh))
    (send frame refresh)
    
    ;; make a computer move, if supposed to
    (unless user-first
      (computer-moves))))

(define (make-move-at pos)
  ;; Make move at pos, return #f if pos is not empty
  (if (empty-position? main-board pos)
      (begin 
        (send (list-ref canvases pos) set-character current-move)
        (send (list-ref canvases pos) refresh)
        (vector-set! main-board pos current-move)
        (set! move-count (+ 1 move-count))
        (if (has-won? main-board current-move)
            (end-game)
            (toggle-current-move)))
      #f))

(define (end-game)
  ;; Color Winning moves 
  ;; Lock game board setting game-finished true
  (for ([i win-move])
    (send (list-ref canvases i) set-color (make-object color% "black"))
    (send (list-ref canvases i) refresh))
  (set! game-finished #t)
  (set! new-game #t))

(define (empty-position? board pos)
  (char=? (vector-ref board pos) #\Space))

(define (other-move move)
  ;; return the reverse of move
  (if (char=? move #\X) #\O #\X))

(define (toggle-current-move)
  ;; toggle current move between X and O
  (set! current-move (other-move current-move)))

(define (toggle-user-move)
  ;; toggle user move between X and O
  (set! user-move (other-move user-move)))

(define (toggle-computer-move)
  ;; toggle computer move between X and O
 (set! computer-move (other-move computer-move)))

(define (get-legal-moves board)
  ;; Get the unoccupied (empty) positions on board
  (for/list ((i '(0 1 2 3 4 5 6 7 8))
             #:when (char=? (vector-ref board i) #\Space))
    i))

(define (full-board? board)
  ;; Check whether the board is full or not
  (not (for/or ((v board))
         (char=? v #\Space))))

(define-syntax operate-on-wpath 
  ;; Execute the given func on each of winning paths, (0 1 2), (0 3 6), (0 4 8)  ...
  ;; For example, (operate-on-wpath +) will sequentially run (+ 0 1 2) (+ 0 3 6) ....
  (syntax-rules ()
    ((operate-on-wpath func)
     (for ((lst win-paths))
       (func (list-ref lst 0) (list-ref lst 1) (list-ref lst 2))))))
  
(define (check-possible-winning-paths board move)
  ;; Return total number of possible winning paths
  (let ((paths 0))
    (let-syntax 
        ((possible-winning-path?
          ;; We are going to operate this on win-paths
          ;; If any path in (win-paths), has the opposite of move
          ;;        it is not possible for move to win in that path.
          ;; Otherwise, it is a potential win move. Increase paths.
          (syntax-rules ()
            ((is-empty-or-move p1 p2 p3)
             (when (not (or (char=? (vector-ref board p1) (other-move move))
                            (char=? (vector-ref board p2) (other-move move))
                            (char=? (vector-ref board p3) (other-move move))))
               (set! paths (+ paths 1)))))))
      (operate-on-wpath possible-winning-path?)
      paths)))

(define (is-more-likely-to-win? board move)
  ;; Evaluation function, only by using possible winning paths, is not good enough
  ;; That is the user still beat the computer ...
  ;; So this one check any path of winning paths has two of moves
  ;; if so increase score by two ...
  (let ((score 0))
    (let-syntax
        ((path-has-two-move
          (syntax-rules ()
            ((path-has-two-move p1 p2 p3)
             (when (or (and (char=? (vector-ref board p1)
        (vector-ref board p2) move)
       (not (char=? (vector-ref board p3) (other-move move))))
                       (and (char=? (vector-ref board p1)
        (vector-ref board p3) move)
       (not (char=? (vector-ref board p2) (other-move move))))
                       (and (char=? (vector-ref board p2)
        (vector-ref board p3) move)
       (not (char=? (vector-ref board p1) (other-move move)))))
               (set! score (+ score 1)))))))
      (operate-on-wpath path-has-two-move))
    score))

(define (has-won? board move)
  ;; Decide whether the given move ( X or O ) has won on board 
  ;; If there is a winning move, set win-move, so that we could highlight
  (let-syntax ((has-won-syn
                (syntax-rules ()
                  ((has-won-syn p1 p2 p3)
                   (if (char=? (vector-ref board p1)
          (vector-ref board p2)
          (vector-ref board p3) move)
                       (set! win-move (list p1 p2 p3))
                       #f)))))                       
    (for/or ((pos win-paths))
      (has-won-syn (list-ref pos 0) (list-ref pos 1) (list-ref pos 2)))))

(define (get-position-by-minmax)
  ;;; Implementation of two-ply minmax
  (letrec ((position 0)  
           (eval-function
     (lambda (board move)
       (let ((m (check-possible-winning-paths board move))
      (o (check-possible-winning-paths board (other-move move))))
  (let ((lm (is-more-likely-to-win? board move))
        (lo (is-more-likely-to-win? board (other-move move))))
                  (- (+ m (* 2 lm)) (+ o (* 2 lo)))))))


           (max-turn (lambda (board move depth)
                       (cond 
   ((has-won? board (other-move move)) -10)
   ((or (full-board? board)
        (= depth 2)) (eval-function board move))
   (else
    (let ((maximum -1024))                            
      (for ((i (get-legal-moves board)))
    (let ((vec (make-vector 9 #\Space)))
      (vector-copy! vec 0 board)            
      (vector-set!  vec i move)
      (let ((tmp (min-turn vec (other-move move) (+ 1 depth))))
        (when (> tmp maximum)
       (set! maximum tmp)
       (when (= depth 0)
      (set! position i))))))
      maximum)))))
           
           (min-turn (lambda (board move depth)
                       (cond 
   ((has-won? board (other-move move)) 10)
   ((or (full-board? board)
        (= depth 2)) (eval-function board move))
   (else
    (let ((minimum 1024)) 
      (for ((i (get-legal-moves board)))
    (let ((vec (make-vector 9 #\Space)))
      (vector-copy! vec 0 board)            
      (vector-set!  vec i move)
      (let ((tmp (max-turn vec (other-move move) (+ 1 depth))))
        (when (< tmp minimum)
       (set! minimum tmp)))))
      minimum))))))
    
    (max-turn main-board current-move 0)
    position))

(define (computer-moves)
  ;; Make a computer move based on minmax algorithm
  (unless (full-board? main-board)
   (make-move-at (get-position-by-minmax))))

;;; Gui ;;;
(define frame 
  (new frame% 
       [label "Tic Tac Toe"]
       [width 400]
       [height 400]))

(define menu-bar 
  (new menu-bar% 
       [parent frame]))

(define file-menu 
  (new menu% 
       [label "&File"]
       [parent menu-bar]))

(define new-menu 
  (new menu-item% 
       [label "&New Game"]
       [parent file-menu]
       [callback (lambda (i e) (prepare-new-game))]
       [shortcut #\n]))

(define quit-menu 
  (new menu-item% 
       [label "&Quit"]
       [parent file-menu]
       [callback (lambda (i e) (send frame show #f))]
       [shortcut #\q]))

(define edit-menu
  (new menu%
       [label "&Edit"]
       [parent menu-bar]))

(define use-menu 
  (new checkable-menu-item%
       [label "&Use X"]
       [parent edit-menu]
       [checked #t]
       [callback (lambda (i e) 
                   (toggle-user-move)
                   (toggle-computer-move))]))

(define start-menu 
  (new checkable-menu-item% 
       [label "&Start First"]
       [parent edit-menu]
       [checked #t]       
       [callback (lambda (i e) 
                   (when (or new-game game-finished)
                     (prepare-new-game)))]))
(define help-menu
  (new menu%
       [label "&Help"]
       [parent menu-bar]))

(define about-menu
  (new menu-item%
       [label "A&bout"]
       [parent help-menu]
       [callback (lambda (i e) (void))]))

(define main-pane
  (new vertical-pane%
       [parent frame]
       [vert-margin 5]
       [horiz-margin 5]
       [spacing 5]))

(define upper-pane
  (new horizontal-pane%
       [parent main-pane]
       [spacing 5]))

(define middle-pane
  (new horizontal-pane%
       [parent main-pane]
       [spacing 5]))

(define lower-pane
  (new horizontal-pane%
       [parent main-pane]
       [spacing 5]))

(define canvas-box%
  (class canvas%
    (init-field [character #\Space]
                [position 0]
                [color (make-object color% "gray")])
    
    (inherit get-dc)
    
    (define/override (on-event e)
      (when (equal? (send e get-event-type) 'left-down) 
        ;; When left-button is pressed
        (unless (or (full-board? main-board) game-finished)
          (when new-game
            ;; If it is a new game, aka first click, load settings
            (prepare-new-game))
          (when (make-move-at position)
            ;; make-move-at return #f if the position is not empty
            (unless game-finished 
              ;; If the game is not finished yet, computer turn
              (computer-moves))))
        (let ((dc (get-dc)))
          (send dc clear))
        (send this refresh)))
    
    (define/override  (on-paint)
      ;; Handles Drawing of char X or O according to color 
      (let ((dc (get-dc)))        
        (let-values (((x y) (send this get-size)))
          (send dc set-text-foreground color)
          (send dc set-font (make-object font% 50 'default))
          (send dc draw-text (string character) (/ (- x 50) 2) (/ (- y 75) 2)))))
    
    (define/public (set-color c)
      (set! color c))
    
    (define/public (set-character char)
      (set! character char))
    
    (super-new)))

(define canvases
  (let ((canvas-one (new canvas-box%
                         [position 0]
                         [parent upper-pane])) 
        (canvas-two (new canvas-box%
                         [position 1]
                         [parent upper-pane]))
        (canvas-three (new canvas-box%
                           [position 2]   
                           [parent upper-pane]))
        (canvas-four (new canvas-box%
                          [position 3]  
                          [parent middle-pane]))
        (canvas-five (new canvas-box%
                          [position 4]  
                          [parent middle-pane]))
        (canvas-six (new canvas-box%
                         [position 5]
                         [parent middle-pane]))
        (canvas-seven (new canvas-box%
                           [position 6]   
                           [parent lower-pane]))
        (canvas-eight (new canvas-box%
                           [position 7]       
                           [parent lower-pane]))
        (canvas-nine (new canvas-box%
                          [position 8]
                          [parent lower-pane])))  
    (list canvas-one canvas-two canvas-three 
          canvas-four canvas-five canvas-six 
          canvas-seven canvas-eight canvas-nine)))

(send frame center 'both) ;; position frame at center of the screen
(send frame show #t)  ;; display frame

