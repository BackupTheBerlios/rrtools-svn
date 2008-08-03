IEC-ATA v2 software 1.35.3
==========

This short document briefly describes the IEC-ATA v2 hard drive
controller. 
The Dienstagstreff has take the original IEC-ATA from 

Asbjørn Djupdal
Grønngjelet 50
4640 SØGNE
NORWAY
djupdal@idi.ntnu.no
Homepage: http://www.stud.ntnu.no/~djupdal/cbm/iecata/

If you need more information, don't hesitate to ask us
directly. 

Homepage: http://www.dienstagstreff.de

Introduction
------------

IEC-ATA is a hard drive controller for the Commodore IEC serial bus.
It enables all computers that has an IEC serial bus port (e.g VIC-20,
C-64, C-128) to use cheap, easy to get ATA hard drives (also called
IDE hard drives). 

Features
--------

- Supports standard ATA hard drives up to 128 gigabytes.
  They must have LBA mode.

- The whole disk is available as one big partition

- Supports standard Commodore KERNAL IEC disk commands. This has a
  number of implications:
  - May be connected to any computer with an IEC serial bus port
    (VIC-20, C-64, C-128, and probably others...)
  - No driver software is necessary on the computer, the hard drive
    works like a disk drive with a giant disk in it
  - The IEC bus is very slow, making the hard drive slow. But it is
    considerably faster than the 1541 disk drive. 

- Custom file system adfs1.1 (not compatibel to adfs 1.0 of 
  version 1.3) that has the following features:
  - Supports PRG, USR, SEQ, DEL and REL(only sequential) file types, 
    and a new DIR file type that represents subdirectories
  - Smallest addressable unit: 512 bytes (one ATA logical block)
  - Max file size: 32 megabytes
  - Max number of directory entries: 65535
  - Max number of nested subdirectories: unlimited
   
Usage
-----

Connect the IEC-ATA board to the computer and to the ATA disk drive,
and power on. If the error light does not turn off after some seconds,
try a reset. If that does not help, there is a problem with the hard
drive.

The hard drive has the drive number 14 or outher (as opposed to the 1541 that is
usually drive 8). Other than that, the hard drive is used in the same
way that a 1541 disk drive. 

In a spezial rom version fast vic-20 timing is used (does not work with C64). 
If a file start with a "." it is unvisible.
The following disk commands are supported (through disk channel 15):

- CD:<subdir>
  Change directory
- CD<- (this is chr$(95))
  one directory up
- CD/
  to root directory
- CD:/<subdir1>/<subdir2>...
  Dir phases are posibele 
- MD:<subdir>
  Make subdirectory
- RD:<subdir>
  Remove (delete) subdirectories. The subdirectory must be empty
- S:<file> not ok
  Scratch (delete) files
- R:<new-file>=<old-file>
  Rename file
- N:diskname,id
  Format disk. 
- I
  Initialize disk (is actually ignored by IEC-ATA)
- U0>chr$(dev)
  change the devienmber tempurary to dev
- UJ
  make a reset the dev Nr stay
- with jiffidos @t is working

- new kommands with no funktion jet: M-W, M-R, M-E

- new kommands wiht no funktion in long and short version: B-R, B-W, B-E, B-A, B-F

The syntax of these commands are the same as on Commodore DOS. Where
appropriate, you may use wildcards (* and ?) just like on Commodore
DOS. 
Loading and saving files work just like on a 1541 disk drive. 
In this version it is possible to use GET#, INPUT# and PRINT# in Basic.
If you read the error channel (channel 15), you get one of these
messages: 

- 00: No error
- 74: DRIVE NOT READY , the hard drive does not have a valid file
      system
- 25: Create error, the file or directory you try to create can not be
      created
- 61: FILE NOT OPEN error, you are trying to access a file that is not open
- 62: FILE NOT FOUND error, the file or directory is not found


- 30: SYNTAX ERROR
- 31: SYNTAX ERROR
- 32: SYNTAX ERROR
- 73: Version message, this is shown after startup and gives the
      version of the IEC-ATA software. 

Examples of use
---------------

Loading a file from BASIC:

  LOAD"filename",14

Saving a file from BASIC:

  SAVE"filename",14

Loading the directory:

  LOAD"$",14

Changing the directory:

  OPEN1,14,15,"CD:mydir":CLOSE1

Formatting the disk:fast without check the size

  OPEN1,14,15,"N:name":CLOSE1
  
Formatting the disk:

  OPEN1,14,15,"N:name,id":CLOSE1

Change the devicenumber temporary to 9

  OPEN1,14,15,"U0>"+chr$(9):CLOSE1

Open a file to write in Basic  

  OPEN1,14,1,"filename"

Write data in A$ to a file
 
  PRINT#1,A$ 

Open a file to read in Basic  

  OPEN1,14,2,"filename,s,r"

Read a cuple of data from a file to basic

  INPUT#1,A$

Read one data to A$

  GET#1,A$

Close a file

  CLOSE1



Hardware
--------

The IEC-ATA controller card contains an AVR atmega162 microcontroller with
32 kilobytes of external SRAM. For more information about the
hardware, see the included schematics.

--
 dienstagtreff, 2007, Asbjørn Djupdal, 2002
