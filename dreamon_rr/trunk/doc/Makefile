# -------------------------------------
#
#   Makefile for Docs
#
# -------------------------------------

ADMON_GRAPHICS=gfx/*.gif


all: eng ger history_standalone

.PHONY: all clean eng ger history_standalone gfx

#--------------------------------------

eng: eng.sgml history.sgml dreamslogo.sgml cygnus-html.dsl cygnus-onehtml.dsl cygnus-print.dsl
	rm -fr eng/
	mkdir eng/
	cd eng/ && jade -t sgml -ihtml -d ../cygnus-html.dsl ../eng.sgml && cd ..
	mkdir eng/gfx
	cp $(ADMON_GRAPHICS) eng/gfx
	jade -t sgml -ihtml -d cygnus-onehtml.dsl eng.sgml >eng.html
	links -dump eng.html >eng.txt
	db2dvi -d cygnus-print.dsl eng.sgml
	dvipdft -o dreamon_eng.pdf eng.dvi
	zip -r -9 dreamon_aeng.zip eng.txt
	zip -r -9 dreamon_heng.zip eng/
	zip -r -9 dreamon_peng.zip dreamon_eng.pdf


ger: ger.sgml history.sgml dreamslogo.sgml cygnus-html.dsl cygnus-onehtml.dsl cygnus-print.dsl
	rm -fr ger/
	mkdir ger/
	cd ger/ && jade -t sgml -ihtml -d ../cygnus-html.dsl ../ger.sgml && cd ..
	mkdir ger/gfx
	cp $(ADMON_GRAPHICS) ger/gfx
	jade -t sgml -ihtml -d cygnus-onehtml.dsl ger.sgml >ger.html
	links -dump ger.html >ger.txt
	db2dvi -d cygnus-print.dsl ger.sgml
	dvipdft -o dreamon_ger.pdf ger.dvi
	zip -r -9 dreamon_ager.zip ger.txt
	zip -r -9 dreamon_hger.zip ger/
	zip -r -9 dreamon_pger.zip dreamon_ger.pdf


history_standalone: history_standalone.sgml history.sgml cygnus-html.dsl cygnus-onehtml.dsl cygnus-print.dsl
	rm -fr history_standalone/
	mkdir history_standalone/
	cd history_standalone/ && jade -t sgml -ihtml -d ../cygnus-html.dsl ../history_standalone.sgml && cd ..
	mkdir history_standalone/gfx
	cp $(ADMON_GRAPHICS) history_standalone/gfx
	jade -t sgml -ihtml -d cygnus-onehtml.dsl history_standalone.sgml >history_standalone.html
	links -dump history_standalone.html >history_standalone.txt

gfx:
	$(MAKE) -C gfx all

#--------------------------------------

clean:
	rm -f eng.txt ger.txt history_standalone.txt
	rm -f dreamon_eng.pdf dreamon_ger.pdf
	rm -f dreamon_aeng.zip dreamon_heng.zip dreamon_peng.zip dreamon_ager.zip dreamon_hger.zip dreamon_pger.zip
	rm -fr eng/ ger/ history_standalone/
	$(MAKE) -C gfx clean

#--------------------------------------


