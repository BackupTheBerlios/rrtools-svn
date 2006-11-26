<!DOCTYPE style-sheet PUBLIC "-//James Clark//DTD DSSSL Style Sheet//EN" [
<!ENTITY % html "IGNORE">
<![%html;[
<!ENTITY % print "IGNORE">
<!ENTITY docbook.dsl SYSTEM "/usr/share/sgml/docbook/stylesheet/dsssl/modular/html/docbook.dsl" CDATA dsssl>
]]>
<!ENTITY % print "INCLUDE">
<![%print;[
<!ENTITY docbook.dsl SYSTEM "/usr/share/sgml/docbook/stylesheet/dsssl/modular/print/docbook.dsl" CDATA dsssl>
]]>
]>

<!-- Cygnus customizations by Mark Galassi -->

<style-sheet>


<style-specification id="print" use="docbook">
<style-specification-body> 

;; ====================
;; customize the print stylesheet
;; ====================

;; make funcsynopsis look pretty
(define %funcsynopsis-decoration%
  ;; Decorate elements of a FuncSynopsis?
  #t)

;; use graphics in admonitions, and have their path be "."
;; NO: we are not yet ready to use gifs in TeX and so forth
(define %admon-graphics-path%
  "gfx/")
(define %admon-graphics%
  #t)

;; this is necessary because right now jadetex does not understand
;; symbolic entities, whereas things work well with numeric entities.
(declare-characteristic preserve-sdata?
          "UNREGISTERED::James Clark//Characteristic::preserve-sdata?"
          #f)
(define %two-side% #t)

(define %section-autolabel% 
  ;; Are sections enumerated?
  #t)
;; (define %title-font-family% 
;;   ;; The font family used in titles
;;   "Ariel")
(define %visual-acuity%
  ;; General measure of document text size
  ;; "presbyopic"
  ;; "large-type"
  "presbyopic")

(define %generate-part-toc% #t)

;; (define %block-start-indent% 10pt)

(define %graphic-default-extension% "eps")

(element div (process-children))

(element linebreak
    (make display-group
          (process-children)))
	  
</style-specification-body>
</style-specification>

<external-specification id="docbook" document="docbook.dsl">

</style-sheet>
