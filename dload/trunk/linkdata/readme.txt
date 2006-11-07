
This folder contains a small demo of how to link data with exomizer and
pucrunch. The demo data is a multicolor bitmap by Franky/Role with a viewer.
It is split up in 4 parts:

bitmap.prg : Bitmap     ($4000-$5f40)
col.prg    : Screen Ram ($6000-$63e8)
d8.prg     : Color Ram  ($6400-$67e8)
viewer.prg : Viewer     ($1000-$1040)

All 4 input files are crunched with exomizer and pucrunch:

exomizer -r -o outputfile.exo inputfile.prg
pucrunch -fshort -c0 inputfile.prg outputfile.puc

Finally all 4 crunched files are appended to one big file.
