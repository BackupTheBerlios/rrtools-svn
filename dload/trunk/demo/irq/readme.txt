Irq Example
----------------

This example changes the vic bank during loading.


Start
-----

To run this example, load the files 'irqdemo' and 'dload' from the d64 image.
Start the code at $c000.


Filelist:
--------

Jamfile		: jam rules for this examples, run jam in the main directory to build it
dload.cfg	: dload configuration
dload.prg	: dload object code
irqdemo.d64	: 1541 diskimage with all object files of this example
irqdemo.d81	: 1581 diskimage with all object files of this example
irqdemo.dfi	: dfi image with all object files of this example
irqdemo.lnx	: lynx archive with all object files of this example
irqdemo.prg	: irq routine, object code
irqdemo.src	: irq routine, source
readme.txt	: this text
test.prg	: example data to load

