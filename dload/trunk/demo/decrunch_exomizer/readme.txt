Decrunch Example
----------------

This example shows the combination of DLoads Open/Get Interface with exomizer.


Start
-----

To run this example, load the files 'decrunch' and 'dload' from the d64 image.
Start the code at $c000.


Filelist:
--------

Makefile	: make rules for this examples, run Gnu Make to build it
decrunch.d64	: diskimage with all object files of this example
decrunch.prg	: decrunch object code
decrunch.src	: decrunch source
dload.cfg	: dload configuration
dload.prg	: dload object code
readme.txt	: this text
test.prg	: example data to load, packed with 'exomizer -r'
