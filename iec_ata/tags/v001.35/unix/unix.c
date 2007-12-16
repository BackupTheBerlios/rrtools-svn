/*
     IEC-ATA, a hard drive controller for the CBM IEC bus 
     Copyright (C) 2002  Asbjørn Djupdal
     
     This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
     as published by the Free Software Foundation; either version 2
     of the License, or (at your option) any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

     ----

     The author of IEC-ATA may be reached by electronic mail:
     
       djupdal@idi.ntnu.no

     or if the email address no longer is valid, by paper mail:

       Asbjørn Djupdal
       Grønngjelet 50
       4640 SØGNE
       NORWAY
*/

/*
  unix.c
  A unix program that uses the IEC-ATA file system to access a real
  harddrive or a disk-file. 

  NOTE: This program is written in a quick and dirty way, and is used
  for debugging purposes only. It is only made public to show how the
  IEC-ATA file system routines may be used in a UNIX program. 
*/

#include "../iecata.h"

#include "../dos-file.c"
#include "../dos-dir.c"
#include "../dos-init.c"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* protos *****************************************************************/

int main (int argc, char *argv[]);

/* variables **************************************************************/

FILE *fp; /* the HD */
block_t totalDiskSize = 100000; /* TODO: get this number from the
                                   actual hard drive */

/* functions **************************************************************/

int main (int argc, char *argv[]) {
  if (argc == 2) {

    /* open file to the entire hard drive */
    if ((fp = fopen (argv[1], "r+b"))) {

      /* init file system */
      if (!dosInit()) {
        fprintf (stderr, "disk not formatted!\n");
      }

      /* main loop, accept and execute commands */
      while (TRUE) {
        char cmdline[256];
        char *cmd;
    
        printf ("Command [h for help]> ");
        fflush(stdout);

        fgets (cmdline, 256, stdin);

        if ((cmd = strtok (cmdline, " \t\n"))) {

          if (!strcmp (cmd, "h") || !strcmp (cmd, "help")) {
            puts ("\n***** iec-ata emulation/debugging system *****");
            puts ("h                                   : This text");
            puts ("format                              : Format disk");
            puts ("mkdir <name>                        : Make  directory");
            puts ("rmdir <name>                        : Remove directory");
            puts ("ls                                  : List directory");
            puts ("cd <path>                           : Change directory");
            puts ("export <iecata name> <unix-file>    : Export file");
            puts ("import <unix-file> <iecata name>    : Import file");
            puts ("rm <name>                           : Delete file");
            puts ("b <blocknumber>                     : Show disk block");
            puts ("q                                   : Exit program");
            puts ("");
          } else if (!strcmp (cmd, "format")) {
            if (formatDrive ()) {
              printf ("format OK\n");
            }
          } else if (!strcmp (cmd, "mkdir")) {
            char *name = strtok (NULL, " \t\n");

            if (name) {
              if (createDir (name)) {
                printf ("mkdir OK\n");
              }
            }
          } else if (!strcmp (cmd, "rmdir")) {
            char *name = strtok (NULL, " \t\n");

            if (name) {
              deleteDir (name);
              printf ("rmdir OK\n");
            }
          } else if (!strcmp (cmd, "ls")) {
            entryIndex_t entryIndex = 0;
            struct dirEntryStruct *entry;

            while ((entry = getEntry (entryIndex++))) {
              if (entry->startBlock) {
                char filename[17];

                strncpy (filename, entry->fileName, 16);
                filename[16] = 0;

                printf ("%10d bytes  %c%c  %s,%s\n", 
                        entry->fileType == DIR ? 0 :
                        (entry->fileSize - 1) * BLOCKSIZE +
                        entry->bytesInLastBlock,
                        entry->readOnly ? '<' : ' ',
                        entry->splat ? '*' : ' ',
                        filename,
                        entry->fileType == PRG ? "prg" :
                        entry->fileType == SEQ ? "seq" : "dir");
              }
            }
          } else if (!strcmp (cmd, "cd")) {
            char *path = strtok (NULL, " \t\n");

            if (path) {
              setCurrentDir (path);
            }
          } else if (!strcmp (cmd, "export")) {
            FILE *fp2;
            char *name1 = strtok (NULL, " \t\n");
            char *name2 = strtok (NULL, " \t\n");
          
            if (name1 && name2) {
              if (openRead (name1, ANY, 2)) {
                channelTable[2].fileState = READ_FILE;

                if ((fp2 = fopen (name2, "wb"))) {
                  bool_t eof = FALSE;
                  
                  while (!eof) {
                    bufferSize_t size = BLOCKSIZE;

                    readFile (2, &eof);
                    if (eof) size = channelTable[2].dirEntry.bytesInLastBlock;
                    fwrite (&channelTable[2].buffer, 1, size, fp2);
                  }
                  fclose (fp2);
                }
                closeFile (2);
              }
            }
          } else if (!strcmp (cmd, "import")) {
            FILE *fp2;
            char *name1 = strtok (NULL, " \t\n");
            char *name2 = strtok (NULL, " \t\n");

            if (name1 && name2) {
              if ((fp2 = fopen (name1, "rb"))) {
                if (openWrite (name2, PRG, 2)) {
                  bufferSize_t size = BLOCKSIZE;
                
                  channelTable[2].fileState = WRITE_FILE;

                  while (size == BLOCKSIZE) {
                    size = fread (&channelTable[2].buffer, 1, BLOCKSIZE, fp2);
                    if (size != BLOCKSIZE) {
                      channelTable[2].bufferPtr = size;
                    } else if (!writeFile (2)) {
                      fprintf (stderr, "Error while writing\n");
                      break;
                    }
                  }
                  closeFile (2);
                }
                fclose (fp2);
              } else fprintf (stderr, "can't open file\n");
            }
          } else if (!strcmp (cmd, "rm")) {
            char *name = strtok (NULL, " \t\n");
          
            if (name) {
              deleteFile (name);
            }
          } else if (!strcmp (cmd, "b")) {
            block_t block[BLOCKSIZE / sizeof (block_t)];
            uint16_t i;
            char *blkNumber = strtok (NULL, " \t\n");

            if (blkNumber) {
              ataGetBlock (atoi (blkNumber), (uint8_t *)block);
            
              for (i = 0; i < BLOCKSIZE / sizeof (block_t); i++) {
                printf ("%d ", block[i]);
              }
              printf ("\n");
            } else printf ("arg error\n");
          } else if (!strcmp (cmd, "q")) {
            exit (0);
          } else {
            fprintf (stderr, "Unknown command\n");
          }
        }
      }
    } else fprintf (stderr, "Can not open %s\n", argv[1]);
  } else fprintf (stderr, "Usage: %s <device>\n", argv[0]);
  exit (0);
}

void ataGetBlock (block_t blockNumber, uint8_t data[]) {
  if ((fseek (fp, blockNumber * BLOCKSIZE, SEEK_SET)) != -1) {
    if (fread (data, 1, BLOCKSIZE, fp) != BLOCKSIZE) {
      fprintf (stderr, "Error while reading block\n");
    }
  } else fprintf (stderr, "Can't seek to block\n");
}

void ataPutBlock (block_t blockNumber, uint8_t data[]) {
  if ((fseek (fp, blockNumber * BLOCKSIZE, SEEK_SET)) != -1) {
    if (fwrite (data, 1, BLOCKSIZE, fp) != BLOCKSIZE) {
      fprintf (stderr, "Error while writing block\n");
    }
  } else fprintf (stderr, "Can't seek to block\n");
}

