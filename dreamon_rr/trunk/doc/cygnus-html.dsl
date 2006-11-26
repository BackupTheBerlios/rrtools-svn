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


<!--
;; ====================
;; customize the html stylesheet
;; ====================
-->
<style-specification id="html" use="docbook">
<style-specification-body> 

;; this is necessary because right now jadetex does not understand
;; symbolic entities, whereas things work well with numeric entities.
(declare-characteristic preserve-sdata?
          "UNREGISTERED::James Clark//Characteristic::preserve-sdata?"
          #f)

;; put the legal notice in a separate file
(define %generate-legalnotice-link%
  #t)

;; use graphics in admonitions, and have their path be "stylesheet-images"
;; NO: they do not yet look very good
(define %admon-graphics-path%
  "gfx/")
(define %admon-graphics%
  #t)

;; make funcsynopsis look pretty
(define %funcsynopsis-decoration%
  ;; Decorate elements of a FuncSynopsis?
  #t)

(define %html-ext% ".html")
(define %body-attr%
  ;; What attributes should be hung off of BODY?
  (list
   (list "BGCOLOR" "#FFFFFF")
   (list "TEXT" "#000000")))

(define %generate-article-toc% 
  ;; Should a Table of Contents be produced for Articles?
  ;; If true, a Table of Contents will be generated for each 'Article'.
  #t)

(define %generate-part-toc% #t)

(define %shade-verbatim%
  #t)

(define %use-id-as-filename%
  ;; Use ID attributes as name for component HTML files?
  #t)

(define %graphic-default-extension% "gif")

(define %root-filename% "index")

(element (epigraph div)
  (make element gi: "DIV"
          (make element gi: "I"
	              (process-children-trim))))
		      
(element div ($paragraph$))

(element linebreak
  (make empty-element gi: "BR"))
  
</style-specification-body>
</style-specification>



<external-specification id="docbook" document="docbook.dsl">

</style-sheet>
