/*
     IEC-ATA, a hard drive controller for the CBM IEC bus 
     Copyright (C) 2002  Asbj�rn Djupdal
     
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

       Asbj�rn Djupdal
       Gr�nngjelet 50
       4640 S�GNE
       NORWAY
	   edit by Dienstagstreff
*/



/*
  iecata.c V1.33.3
  The main source file for the IEC-ATA software, contains main()
*/

#include "iecata.h"


#define UART_DEBUG //enable uart debugging
#define ATA_ADDRESSLATCH//changed connection of pins to free uart

#ifdef UART_DEBUG
	#define DGB_PRINT(s) uart_putstr(s)
#else
	#define DGB_PRINT(s)
#endif


/* include c-files instead of linking; saves program space because
   functions may be declared inline and extern */


#ifdef UART_DEBUG
	#include "uart.c"
#endif

#include "ata.c"
#include "iec.c"
#include "dos-file.c"
#include "dos-dir.c"
#include "dos-init.c"
#include "readdir.c"
#include "mem.c"

/* error numbers, given in bcd */


/* protos ****************************************************************/

void init (void);
void updateLED (void);
bool_t readStatus (struct channelTableStruct *channel);
bool_t readDir (struct channelTableStruct *channel);
static void parseCommand (void);
void parseName (struct channelTableStruct *channel);

int main (void);

/* variables *************************************************************/
volatile int track= 0;
volatile int sector=0;
volatile uint8_t command;
volatile uint8_t error;
volatile uint8_t channelNumber;
jmp_buf attention_jmp;
uint8_t commandBuffer[BLOCKSIZE];
 bufferSize_t bytesReceived;
/* functions *************************************************************/


void init_xram (void) __attribute__ ((naked)) \
    __attribute__ ((section (".init1")));

void
init_xram (void)
{
	MCUCR = (1<<SRE);
}


inline extern void init (void) {
  /* enable external SRAM */
  sbi (MCUCR, SRE);

  /* set up I/O pins */

  DDRA = 0;
  PORTA = 0;  
  
  DDRB = 0x57;
  PORTB = 0x57;
  
  DDRC = 0;
  PORTC = 0;
 
  DDRD = 0xFB;
  PORTD = 0xFB;
  
  DDRE = 0x06;
  PORTE = 0x07;
  
  
  /* enable timer */
  TCCR0 = (1<<CS01); // clk/8

#ifdef UART_DEBUG
  uart_init();
  uart_putstr_P( PSTR("Hallo\r\n") );
#endif

  /* setup interrupt */
  sbi (MCUCR, ISC01);
  cbi (MCUCR, ISC00);
  sbi (GICR, INT0);

  /* init variables */
  command = IDLE;
  attention = FALSE;
  attention_delay = FALSE;
  
  LED_ON;
  
  error = 0x74;
  /* init submodules */
  if (ataInit()) {
    if (dosInit()) {
      error = 0x73;
    }
  }

  /* turn off LED */
  LED_OFF;

  /* Enable interrupts */
  sei();
}




inline extern void updateLED (void) {
	/* blink LED if error <20 */
	if (error>=0x19) {
		static uint16_t cnt;
      
		if (cnt > 600) {
			PORTE ^= (1<<LED_PIN);
			cnt = 0;
		}
		/* timer delay */
		TCNT0 = 0;
		while ( TCNT0 < 200);
		/* update counter */
		cnt++;
	}else if(command != IDLE){
		LED_ON;
	}else{
		LED_OFF;
	}
}



inline extern bool_t readStatus (struct channelTableStruct *channel) {
  uint8_t *buffer = channel->buffer;

  /* error number */
  *(buffer++) = (error >> 4) | '0';
  *(buffer++) = (error & 0x0f) | '0';

  /* space */
  *(buffer++) = ',';
  
  { /* error message */
    uint8_t bufferAdd;
    PGM_P errorMessage;
    
    switch (error) {
      case 0x00:
        errorMessage = PSTR (" OK");
        bufferAdd = 3;
        break;
	case 0x01:
        errorMessage = PSTR ("FILES SCRATCHED");
        bufferAdd = 15;
        break;
    case 0x74:
        errorMessage = PSTR ("DRIVE NOT READY");
        bufferAdd = 15;
        break;
    case 0x63:
        errorMessage = PSTR ("FILE EXIST");
        bufferAdd = 10;
        break;
    case 0x25:
        errorMessage = PSTR ("WRITE ERROR");
        bufferAdd = 11;
        break;
    case 0x61:
        errorMessage = PSTR ("FILE NOT OPEN");
        bufferAdd = 13;
        break;
    case 0x62:
        errorMessage = PSTR ("FILE NOT FOUND");
        bufferAdd = 14;
        break;
    case 0x73:
        errorMessage = PSTR ("IEC-ATA "VERSION);
        bufferAdd = 15;
        break;
    default:
        errorMessage = PSTR ("SYNTAX ERROR");
        bufferAdd = 12;
        break;
    }
    memcpy_P (buffer, errorMessage, bufferAdd);

    buffer += bufferAdd;

    /* clear error */
    error = 0x00;
  }


  /* track and sector (globel)*/
  *(buffer++) = ',';
  *(buffer++) = (track >> 4) | '0';
  *(buffer++) = (track & 0x0f) | '0';
  *(buffer++) = ',';
  *(buffer++) = (sector >> 4) | '0';
  *(buffer++) = (sector & 0x0f) | '0';
  *(buffer++) = '\x0d';  
 
track = 0;
sector = 0;  

  /* record buffer length */
  channel->endOfBuffer = buffer - channel->buffer;

  return TRUE;
}


 
//+++++++++++++++++++++++++++++++++++++++  
void parseCommand (void) {
	uint8_t *comman;
	uint8_t *cmdArg1;
	uint8_t *cmdArg2;
	
   
	comman = commandBuffer;

	ATTENTION_OFF();
	
	/* make message a proper string */
	comman[bytesReceived] = '\0';

	/* get arg1 */
	if ((cmdArg1 = strchr (comman, ':'))) {
		*cmdArg1 = '\0';
		cmdArg1++;
	}else cmdArg1=0;//comman;
  
	/* get arg2 */
	if ((cmdArg2 = strchr (cmdArg1, '='))) {
		*cmdArg2 = '\0';
		cmdArg2++;
	} else cmdArg2 = cmdArg1;

	/* erase possible CR at end of arg2 */
    uint8_t *cr;

    if ((cr = strchr (cmdArg2, 0x0d))) {
      *cr = '\0';
    }
  
	/* interpret and execute command */
    char c1 = *comman;
	
    char c2 = *(comman + 1);
  
    if ((c1 == 'C') && (c2 == 'D')) {
		if (*(comman + 2)=='_'){
			*cmdArg1 = '.';*(cmdArg1+1) = '\0';
		}
	  if (*(comman + 2)=='/'){
			*cmdArg1 = '/';*(cmdArg2+1) = '\0';
		}
      /* change directory */
	  if (*cmdArg1  == '\0' ){
			error = 0x34;}
		else{
			if (!setCurrentDir (cmdArg1)) {
				error = 0x62;
			} 
		}
    } else if ((c1 == 'M') && (c2 == 'D')) {
		/* create directory */
		if (!createDir (cmdArg1)) {
			error = 0x25;
		}
    } else if ((c1 == 'R') && (c2 == 'D')) {
		/* delete directory */
		deleteDir (cmdArg1);
    }  else if (c1 == 'S') {error = 0x1;
		if (cmdArg1!='\0'){
			/* delete file */
			track=(deleteFile (cmdArg1));
		}	else {
			error = 0x34;
		}
		
    } else if (c1 == 'R') {
		/* rename entry */
		if (!renameEntry (cmdArg1, cmdArg2)) {
			error = 0x62;
		}
    } else if ((c1 == 'N')&(cmdArg1!='\0')) {
		/* format drive */
		if ((cmdArg2 = strchr (cmdArg1, ','))) 
			{*cmdArg2 = '\0';}
		if (!formatDrive(cmdArg1,cmdArg2)) {
			error = 0x74;
		}
    } else if (c1 == 'I') {
		/* initialize */
		if (!dosInit()) {
			error = 0x74;
		}
	}else if (c1 == 'U'){ 
		c1=c1 & 0x0f;
		if            (c2 == '0') {
        /* devicenumber change */
			if (*(comman + 2) == '>') {
			    if (*(comman+3)!='\0')	
					{devicenumber = *(comman + 3);}
				else {error = 0x34;
				}
			}
		}else if (c2 == '1'){
		/*block read*/
			
		}else if (c2 == '2'){
		/*block write*/
			
			
		}else if (c2 == 'J'){
		/*hartreset*/
		((void(*)(void))0)(); 
		}else if (c2 == 'I'){
		/*softreset*/
			if (dosInit()) {error = 0x73;} 
		}
	}else  if ((c1 == 'M')){ 
		
		
	}else  if (c1 == 'B'){ 
		
		
		
	} else {
		/* not a valid command */
	if (bytesReceived!=0)	{error = 0x30;}
    }
}

void getBuffer () {
	uint8_t eoi;
	
//(uint8_t *data, bufferSize_t maxBytes, bufferSize_t *bytesReceived
	eoi=	iecListen (commandBuffer, 255, &bytesReceived);
track=bytesReceived;
sector=commandBuffer[0];
	if	 (bytesReceived>=254){
		error = 0x32;
	}
	
	
	return;
}




void parseName (struct channelTableStruct *channel) {
	
	uint8_t *bufferPtr;
	
	bufferPtr = commandBuffer;

	ATTENTION_OFF();
	
	/* make message a proper string */
	bufferPtr[bytesReceived] = '\0';
    
	

	bool_t overwrite 	= FALSE;
	char *filename;
	uint8_t filetype;
	bool_t read;

	

	channel->readDirState = NOT_READ_DIR;

	switch (*bufferPtr) {
		case '@':
			/* overwrite */
			overwrite = TRUE;
			bufferPtr++;
			break;
		case '$':
			/* directory */
			channel->readDirState = READ_DIR_BEGIN;
			bufferPtr++;
			break;
		case '#':
			/*buffer*/
			/*openBuffer(channelNumber) ;*/
			bufferPtr++; /*input buffer pointer*/
		break;
	}

	{ /* skip drive specifier if present */
		char *ptr;
		if ((ptr = strchr (bufferPtr, ':'))) {
			bufferPtr = ptr + 1;/*set buffer pointe behind the :*/
		}
	}

filename = bufferPtr;
//default
filetype = PRG; /* if no , x,y than  take any*/
read = TRUE;
	

	{ /* override file type and direction with data extracted from file name */
    char *ptr = NULL;
		
		do {
			if ((ptr = strchr (bufferPtr, ','))) {
				*ptr = '\0'; /*set at the position of th . a 0 to make sure filename is properly ended */
				bufferPtr = ptr + 1; /*bufferpinter is behint the ,*/
				switch (*bufferPtr) {
					
				case 'P':
					filetype = PRG;
					break;
				case 'S':
					filetype = SEQ;
					break;
				case 'U':
					filetype = USR;
					break;
				case 'L':
					filetype = REL;
					read = FALSE;
					break;
				case 'W':
					read = FALSE;
					break;
				case 'R':
					read = TRUE;
					break;
				case 'A':
					/*open the file read to last byte and add the new byte*/
					break;
				}
			}
		} while (ptr);/*prt is 0 if no , found*/
	}
/* file type and direction */
	switch (channelNumber) {
		case 0:
			/* read  LOAD*/
			read = TRUE;
			break;
		case 1:
			/* write SAVE  */
			read = FALSE;
		break;
	}
	if (channel->readDirState) {
		/* directory */
		if (read) {char *ptr = NULL;
			if ((ptr = strchr (bufferPtr, '='))) {
				*ptr = '\0'; /*set at the position of th . a 0 to make sure filename is properly ended */
				bufferPtr = ptr + 1;
				switch (*bufferPtr) {
					
				case 'P':
					filetype = PRG;
					break;
				case 'S':
					filetype = SEQ;
					break;
				case 'U':
					filetype = USR;
					break;
				case 'L':
					filetype = REL;
					break;
				case 'B':
					filetype = DIR;
				break;
				}
				
			}/*bufferpinter is behint the =*/
			//channel->fileState = READ_FILE;
			/* load "$" or load "$0" ==> filename = "*" */
			if (((*filename == 0) && (*(filename - 1) != ':')) ||
			((*filename == '0') && (*(filename + 1) == 0))) {
				*filename = '*';
				*(filename + 1) = 0;
			}
			/* copy filename (to be used by pattern matching) */
			memcpy (channel->dirEntry.fileName, filename, FILE_NAME_SIZE);
		} 
		
		
	} else {
		closeFile (channelNumber);
		/* normal file */
		if (read) {
			//hierhin kommt er
			/* open file */
			if (!openRead (filename, filetype, channelNumber)) {
				error = 0x62;
			} else {
				channel->fileState = READ_FILE;
			}
		} 
		/*write file */
		else {
			/* delete old file */
			if (overwrite) {
				deleteFile (filename);
			}
			/* open file */
			if (!openWrite (filename, filetype, channelNumber)) {
				error = 0x63;
			} else {
				channel->fileState = WRITE_FILE;
			}
		}
	}
}







int main (void) {
	/* I/O register setup, etc. */
	init();
  
	/* service commanding device */
	if(setjmp(attention_jmp)){
		iecAttention();
	}
	/* main loop */
	while (TRUE) {
		struct channelTableStruct *channel;
		/* Handle delayed Attention requests now */
		ATTENTION_ON();
		
		/* get pointer to channel structure */
		channel = &channelTable[channelNumber];
		/* execute command */
		switch (command) {
			case LISTEN_OPEN: {//A for LOAD SAVE OPEN Filename
				/* reset variables */
				channel->bufferPtr = 0;
				channel->endOfBuffer = 0;
				
				
				getBuffer () ;//
				
				
			break;	
			}
			case UNTALK:
				
				
			break;
				
			case UNLISTEN:
				if (channelNumber == COMMAND_CHANNEL)  {
					/* get command and execute it */
					parseCommand();
				} else {
					/* normal data channel, get file name and open file */
					parseName (channel);
				}
			break;
				
				
			case LISTEN_CLOSE://D LOAD SAVE end CLOSE
				ATTENTION_OFF();
				if (channelNumber == COMMAND_CHANNEL){
					/* close all files */
					uint8_t i;
					for (i = 0; i < 15; i++) {
						closeFile (i);
					}
					
				} else {
					/* close requested file */
					closeFile (channelNumber);
				}
			break;
			case LISTEN_DATA: {//C SAVE PRINT
				if (channelNumber == COMMAND_CHANNEL) {
					/* status channel must be reset before each command */
					/* reset variables */
				channel->bufferPtr = 0;
				channel->endOfBuffer = 0;
					getBuffer () ;
					
				} else {
					if (channel->fileState == WRITE_FILE) {
						bool_t eoi;
						ATTENTION_OFF();
						do {
							bufferSize_t bytesReceived;
							bufferSize_t *bufPtr = &(channel->bufferPtr);
							// receive bytes 
							eoi = iecListen (channel->buffer + *bufPtr, BLOCKSIZE - *bufPtr, &bytesReceived);
							//* update bufferPtr 
							*bufPtr += bytesReceived;
							// save to disk 
							if (*bufPtr == BLOCKSIZE) { 
								
								writeFile (channelNumber);
								
								*bufPtr = 0;
							}
						} while (!eoi);
					} else {
						error = 0x61;
					}
				}
				break;
			} 
			case TALK_DATA: {//B LOAD INPUT GET
			//	if ((channel->fileState == READ_FILE) || (channelNumber == COMMAND_CHANNEL)) {
					bool_t done = FALSE;
					while (!done) {
						static bool_t eof;
						/* get new block of data */
						if (channel->bufferPtr == channel->endOfBuffer) {
							/* start new block at beginning */
							channel->bufferPtr = 0;
							eof = FALSE;
							if (channelNumber == COMMAND_CHANNEL) {
								
								eof = readStatus (channel);//put error in Buffer
								
							} else if (channel->readDirState) {
								
								eof = readDir (channel);
								
							} else {
								ATTENTION_OFF();
								readFile (channelNumber, &eof);
								
								if (eof) {
									channel->endOfBuffer = channel->dirEntry.bytesInLastBlock;
								} else {
									channel->endOfBuffer = BLOCKSIZE;
								}
							}
						}
						ATTENTION_ON();
						/* send data block */
						iecTalk (channel, eof);
						
						done = eof;
					}
					
				break;
			}
		}
		/* blink LED if error condition */
		updateLED();
		
		command = IDLE;
	}
	return 0;
}

uint8_t filenamelen (char *filename) {
	uint8_t len = 0;
  
	while (*filename && (len < 16)) {
		filename++;
		len++;
	}

	return len;
}
