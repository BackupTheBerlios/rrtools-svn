Decrunch Example
----------------

This example shows the combination of DLoads Open/Get Interface with a level
packer.


Start
-----

To run this example, load the files 'decrunch' and 'dload' from the d64 image.
Start the code at $c000.


Filelist:
--------

Jamfile			: jam rules for this examples, run jam in the main directory to build it
decrunch.d64	: 1541 diskimage with all object files of this example
decrunch.d81	: 1581 diskimage with all object files of this example
decrunch.dfi	: dfi image with all object files of this example
decrunch.lnx	: lynx archive with all object files of this example
decrunch.prg		: decrunch object code
decrunch.src		: decrunch source
dload.cfg		: dload configuration
dload.prg		: dload object code
level-squeezer.prg	: the squeezer used for this example
readme.txt		: this text
test.prg		: example data to load, levelpacked with "Level Squeezer V2.0"
