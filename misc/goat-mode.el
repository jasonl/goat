(defvar goat-mode-hook nil)

(defconst goat-font-lock-keywords
  (list
   '("\\<\\(asm\\|class\\|e\\(lse\\|nd\\)\\|i\\(f\\|nclude\\)\\|return\\|self\\)\\>" (1 font-lock-keyword-face)))
  "Keyword highlighting for goat-mode")

(defconst goat-font-lock-functions
  (append goat-font-lock-keywords
	  (list
	   '("\\<\\(\\w+\\): λ" (1 font-lock-function-name-face)))))


(defvar goat-mode-syntax-table nil
  "Goat-mode syntax table")

(if goat-mode-syntax-table
    ()
  (setq goat-mode-syntax-table (make-syntax-table))
  (modify-syntax-entry ?_ "w" goat-mode-syntax-table)
  (modify-syntax-entry ?\; "<" goat-mode-syntax-table)
  (modify-syntax-entry ?\n ">" goat-mode-syntax-table)
  )

;;;###autoload
(defun goat-mode ()
  "Major mode for editing Goat source files"
  (interactive)
  (kill-all-local-variables)
  (set-syntax-table goat-mode-syntax-table)
  (set (make-local-variable 'font-lock-defaults) '(goat-font-lock-functions))
  (message "goat-mode font")
  (setq major-mode 'goat-mode)
  (setq mode-name "Goat")
  (run-hooks 'goat-mode-hook))

(provide 'goat-mode)