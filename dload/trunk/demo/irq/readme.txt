Irq Example
----------------

This example changes the vic bank during loading.


Start
-----

To run this example, load the files 'irqdemo' and 'dload' from the d64 image.
Start the code at $c000.


Filelist:
--------

Makefile	: make rules for this examples, run Gnu Make to build it
dload.cfg	: dload configuration
dload.prg	: dload object code
irqdemo.d64	: diskimage with all object files of this example
irqdemo.prg	: irq routine, object code
irqdemo.src	: irq routine, source
readme.txt	: this text
test.prg	: example data to load

