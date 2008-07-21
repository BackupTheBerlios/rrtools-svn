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
	   edit by Dienstagstreff
*/



/*
  iecata.c V1.33.3
  The main source file for the IEC-ATA software, contains the directrory in two verions
*/

#include "iecata.h"

/* include c-files instead of linking; saves program space because
   functions may be declared inline and extern */ 
   
   uint8_t filenamelen (char *filename);
   
   inline extern bool_t readDir (struct channelTableStruct *channel) {
  bool_t eof = FALSE;
  uint8_t *buffer = channel->buffer;
  static entryIndex_t entryIndex;
  static uint8_t writtenEntries;

if (channel->readDirState == READ_DIR_BEGIN) {
  
    if (channelNumber == 0) {
      memcpy_P (buffer, PSTR ("\x01\x04\x01\x01\x00\x00"
                              "\x12\"IEC-ATA "VERSION" \" AD 2A\x00"), 32);
      buffer += 32;
    } else {
      memset (buffer, 255, 142);
      memcpy_P (buffer, PSTR ("\x41\x00"), 2);
      buffer += 142;
      memset (buffer, 0, 112);
      memcpy_P (buffer, PSTR ("IEC-ATA "VERSION"\xa0\xa0\xa0"
                              "AD\xa0""2A\xa0\xa0\xa0\xa0"), 27);
      buffer += 112;
    }

    /* not begin anymore */
    channel->readDirState = READ_DIR_PROGRESS;
    /* start at dir index 0 */
    entryIndex = 0;
    writtenEntries = 0;
	}
/* put directory */
  while ((channel->readDirState == READ_DIR_PROGRESS) &&
    (buffer < (channel->buffer + BLOCKSIZE - (BASIC_LINE_LENGTH + 20)))) {
		struct dirEntryStruct *entry;
		/* get entry */
		ATTENTION_OFF();
		if ((entry =  getEntry (entryIndex))) {
			
			/* only process non-deleted files */
			if ((entry->startBlock )&&!(*entry->fileName=='.')/*&&!((entry->fileType== DEL)&&(entry->splat))*/){
				
				/* only show files that match pattern */
				if (filenameMatch (entry->fileName, channel->dirEntry.fileName) ||
				!(channel->dirEntry.fileName)) {
					fileSize_t fileSize = entry->fileSize;
					
					{ /* convert fileSize to number of 254 byte blocks (like 1541) */
						fileSize *= 2;
						uint16_t extraBytes = entry->bytesInLastBlock + (fileSize * 2);
						if (fileSize) {
							fileSize--;
						}
						
						while (extraBytes > 258) {
							fileSize++;
							extraBytes -= 254;
						}
					}
					if (channelNumber == 0) {
						/* pointer to next line */
						*(buffer++) = 1;
						*(buffer++) = 1;
						/* linenumber */
						*(buffer++) = (uint8_t)fileSize;
						*(buffer++) = (uint8_t)(fileSize >> 8);
						/* clear line */
						memset (buffer, ' ', BASIC_LINE_LENGTH - 5);
						/* space in beginning of line */
						if (fileSize < 1000) buffer++;
						if (fileSize < 100) buffer++;
						if (fileSize < 10) buffer++;
						{ /* filename */
							uint8_t fileNameSize = filenamelen (entry->fileName);
							/* quotes */
							*(buffer++) = '"';
							/* name */
							memcpy (buffer, entry->fileName, fileNameSize);
							buffer += fileNameSize;
							/* quotes */
							*(buffer++) = '"';
							/* spaces */
							buffer += FILE_NAME_SIZE - fileNameSize;
						}
						/* splat */
						if (entry->splat) *buffer = '*';
						buffer++;
						/* filetype */
						switch (entry->fileType) {
						case DEL:
							memcpy_P (buffer, PSTR ("DEL"), 3);
							break;
						case SEQ:
							memcpy_P (buffer, PSTR ("SEQ"), 3);
							break;
						case USR:
							memcpy_P (buffer, PSTR ("USR"), 3);
							break;
						case PRG:
							memcpy_P (buffer, PSTR ("PRG"), 3);
							break;
						case REL:
							memcpy_P (buffer, PSTR ("REL"), 3);
							break;
						case DIR:
							memcpy_P (buffer, PSTR ("DIR"), 3);
							break;
						}
						buffer += 5;
						if (fileSize > 1000) buffer++;
						if (fileSize > 100) buffer++;
						if (fileSize > 10) buffer++;
						/* TODO: locked */
						/* end of line */
						*(buffer++) = 0;
					} else {
						/* clear direntry */
						memset (buffer, 0, CDOS_DIRENTRY_LENGTH);
						/* file type */
						*buffer = entry->fileType;
						if (entry->fileType > 5) *buffer = 6;
						if (!entry->splat) *buffer |= 0x80;
						/* todo: locked */
						buffer += 3;
						/* name */
						memset (buffer, 160, FILE_NAME_SIZE);
						memcpy (buffer, entry->fileName, filenamelen (entry->fileName));
						buffer += (FILE_NAME_SIZE + 9);
						/* file size */
						*(buffer++) = (uint8_t)fileSize;
						*(buffer++) = (uint8_t)(fileSize >> 8);
						/* write to bytes of 0 if not at end of 1541 block */
						writtenEntries++;
						if (writtenEntries == 8) {
							writtenEntries = 0;
						} else {
							buffer += 2;
						}
					}
				}
			}
			entryIndex++;
		} else {
			if (channelNumber == 0) {
				/* put blocks free */
				memcpy_P (buffer,
				PSTR ("\x01\x01\xff\xf9""BLOCKS FREE.             \x00\x00\x00\x00"),32);
				buffer += 32;
			}
			/* read dir finished */
			channel->readDirState = READ_DIR_FINISHED;
		}
	}

	if (channel->readDirState == READ_DIR_FINISHED) {
		eof = TRUE;
	}

  /* number of bytes to save */
  channel->endOfBuffer = buffer - channel->buffer;

  return eof;
}