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

(defun goat-mode-insert-lambda ()
  "Inserts a λ() sequence"
  (interactive)
  (insert "λ()")
  (backward-char))

(defun goat-mode-insert-equals ()
  "Inserts a ≡ character"
  (interactive)
  (insert "≡"))

(defun goat-mode-insert-not-equals ()
  "Inserts a ≢ character"
  (interactive)
  (insert "≢"))

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
  (run-hooks 'goat-mode-hook)
  (global-set-key (kbd "C-c l") 'goat-mode-insert-lambda)
  (global-set-key (kbd "C-c =") 'goat-mode-insert-equals)
  (global-set-key (kbd "C-c !") 'goat-mode-insert-not-equals)
  )

(provide 'goat-mode)