This directory contains some examples. They are build by executing 'jam' in
the main directory (that's one directory up, where the 'Jamrules' file is).

Each example generates a .d64, .d81 and lynx file with all the necessary files to run it.
Please see the 'readme.txt' in the according directory for more info.


Overview:
--------

decrunch_abcruncher20
  Load a file levelpacked with the ab cruncher v2.0 . Demonstrates the Open/Get interface.

decrunch_exomizer
  Load a file crunched with exomizer. Demonstrates the Open/Get interface.

decrunch_exomizer_link
  Load a file crunched and linked with exomizer. Demonstrates the Open/Get interface.

decrunch_levelsqueezer20
  Load a file levelpacked with the levelsqueezer v2.0 . Demonstrates the Open/Get interface.

decrunch_pucrunch
  Load a file crunched with pucrunch. Demonstrates the Open/Get interface.

decrunch_pucrunch_link
  Load a file crunched and linked with pucrunch. Demonstrates the Open/Get interface.

irq
  Switches the vic bank during loading.

simple
  Just a spimple rasterbar while loading a file.

stresstest
  This test loads 8 files continuously. The files contain random generated data which is protected with a CRC16 checksum.
  NOTE: This test is an endurance test, it only stops after an error.

stresstestget
  The same as 'stresstest', but using the Open/Get interface.
  NOTE: This test is an endurance test, it only stops after an error.

More to come...
--
Baccy.
  