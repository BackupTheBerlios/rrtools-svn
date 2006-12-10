MMC64 Plugins
-------------

The MMC64 features a plugin system. If you hit 'return' on a file in the
browser, the bios looks for a suitable plugin in the 'system64' folder. It
takes the file's extension and appends 'plgin.bin', that's the plugin's
filename.


Examples:

Filename   | Extension | Plugin filename
-----------+-----------+-----------------
pr0n.koa   | koa       | koaplgin.bin
readme.txt | txt       | txtplgin.bin
-----------+-----------+-----------------


The plugin is a normal file with the 2 byte load address. It has no special
plugin header. The bios respects the load address and also takes it as the
plugin's execution address. This means you can use the whole C64 memory for
your plugins (with some little restrictions of course).

When the plugin is entered, the selected file from the filebrowser was not
loaded yet. This is the plugins's task. The bios passes some information
beginning at $cf80. I assigned some labels to the locations:

Address | Length | Label                   | Description
        | /bytes |                         |
--------+--------+-------------------------+-----------------------------------------
$cf80   | 3      | MMCBios_FirstDataSector | first data sector of the FAT filesystem
$cf83   | 3      | MMCBios_FATStartSector  | start sector of the FAT
$cf86   | 1      | MMCBios_SecPerCluster   | sectors per cluster
$cf87   | 4      | MMCBios_FileSize        | filesize in bytes
$cf8b   | 2      | MMCBios_ClusLo          | first cluster of the file's data
--------+--------+-------------------------+-----------------------------------------


These values are necessary to get to the file's data. Take a look at some FAT
filesystem specification for detailed infos. Here is a quick guide how to load
the file:

1) First we determine the file's start sector. Therefore the start cluster
   'MMCBios_ClusLo' must be converted to a sector number:

     FirstSectorOfCluster = (Cluster-2)*MMCBios_SecPerCluster + MMCBios_FirstDataSector

   Do not worry about the multiplication. Legal values for MMCBios_SecPerCluster are only powers of 2, so simple shifting
   can be used instead.

2) Now read up to 'MMCBios_SecPerCluster' sectors starting at
   'FirstSectorOfCluster'. Please note your filelength, there is no special
   end-of-file marker in the sector data.

3) When you have read 'MMCBios_SecPerCluster' sectors you reached the end of a
   cluster. Now the FAT is needed to get the next cluster number.

     FAT_Sector = (OldCluster*2)/BytesPerSector + MMCBios_FATStartSector
     FAT_Offset = (OldCluster*2) modulo BytesPerSector

   BytesPerSector is fixed to 512 bytes for all MMCs I've seen so far.

     FAT_Sector = OldCluster/$100 + MMCBios_FATStartSector
     FAT_Offset = (OldCluster*2) modulo $200

   Now we can split 'OldCluster' in it's high and low byte:

     FAT_Sector = HiByte(OldCluster) + MMCBios_FATStartSector
     FAT_Offset = 2 * LoByte(OldCluster)

   Read sector 'FAT_Sector' and get the two bytes at offset 'FAT_Offset' as
   your new cluster. Continue at step (1).

That's all. It is quite easy to implement, but for a quickstart I prepared some
routines for you. Here are the files:

mmc64_plugin.src : routines to load a file from a MMC64 plugin
koaplgin.src     : demo plugin (displays koala pictures from *.koa files)
Makefile         : use this to build the plugin if you have Gnu-Make installed
readme.txt       : message from the past

All sources are written for the Dreamass assembler, an open source,
cross-platform assembler. Grab your copy here:

<http://people.freenet.de/LittleDreamLand/dreamass>

The most important part of the 'mmc64_plugin.src' source are these 4 routines:

 * MMC64Plugin_Init

   Initialize the MMC64 register, save the zeropage and init the plugin
   variables. This function should be called right at the start of a plugin.


 * MMC64Plugin_OpenFile

   Open the file selected in the filebrowser.


 * MMC64Plugin_GetByte

   Reads one byte from the file opened with above function.


 * MMC64Plugin_Exit

   Restore the zeropage and the control register, returns to the filemanager.

A very simple plugin looks like this:


        ; init the plugin variables
        jsr MMC64Plugin_Init

loadData:
        jsr MMC64Plugin_GetByte
        bcs load_eoferr

        ; process data here

        jmp loadData

load_eoferr:
        lsr
        bcc eof

        ; load error! show message

eof:
        jmp MMC64Plugin_Exit

Take a look at the 'koaplgin.src' source for a more detailed example.

NOTE:
Reenter MMC Menu from RR: Poke 57105,24
--
Doc Bacardi


           ______              ______              ___________
         __\     \    ______ __\     \    ______ __\          \    ______
        /\  \_____\ __\     \   \_____\ __\     \   \__________\ __\     \
       /  \__\__   \_  \_____\ __\__   \_  \_____\ __\_______   \_  \_____\
      /   /    /    /\__\__   \_   /____/\__\__   \_   /    /    /\__\__   \_
     /   /    /    / /   _/    /  ___/_  /   _/    /  /    /    / /    /____/
     \  /    /    / /    \____/  /    / /    \    /  /    /    / /\___    \
      ./_________/ /    /    /_______/ /    /    /__/____/    /\/    /    /
                 \/____/    /        \/____/    /      \/_____\ \________/
                     \/_____\            \/_____\
                  cRu/1oo
                    .                       `http://www.the-dreams.de'


