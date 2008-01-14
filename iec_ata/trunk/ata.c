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
*/

/*
  ata.c V1.31
  Contains the code for low level disk access
*/

#include "iecata.h"


//set this when wires normally connected to PD0 and PD1
//go to the Latch 0 and 1 instead (to free the serial port)

//#define OLD_BOARD
//#define ATA_ADDRESSLATCH // FOR TXRX (NEW BORD)
#define NEW_BOARD

#ifdef OLD_BOARD
	//defines for original PCB
	

	#define ATA_DIOW   PB1
	#define ATA_DIOR   PB2

	#define ATA_REG_DATA            0x10
	#define ATA_REG_ERROR           0x30
	#define ATA_REG_SECTORS         0x50
	#define ATA_REG_LBA0            0x70
	#define ATA_REG_LBA1            0x90
	#define ATA_REG_LBA2            0xb0
	#define ATA_REG_LBA3            0xd0
	#define ATA_REG_COMMAND         0xf0
	#define ATA_REG_ALT_STATUS      0xc8
	#define ATA_REG_DRIVE_ADDR      0xe8
#else
// NEW_BOARD
	//defines for Dienstagstreff PCB by Suschman

	#define ATA_DIOW   PB0
	#define ATA_DIOR   PB1

	#define ATA_REG_DATA            0x02
	#define ATA_REG_ERROR           0x06
	#define ATA_REG_SECTORS         0x0A
	#define ATA_REG_LBA0            0x0E
	#define ATA_REG_LBA1            0x12
	#define ATA_REG_LBA2            0x16
	#define ATA_REG_LBA3            0x1A
	#define ATA_REG_COMMAND         0x1E
	#define ATA_REG_ALT_STATUS      0x19
	#define ATA_REG_DRIVE_ADDR      0x1D
#endif


#define ATA_CMD_READ_SECT       0x21//  20 in moderneren laufwerken vorhanden
#define ATA_CMD_WRITE_SECT      0x31//  30 in moderneren laufwerken vorh
#define ATA_CMD_IDENTIFY_DRIVE  0xec

#define STATUS_DRDY             0x40
#define STATUS_BSY              0x80
#define STATUS_DRQ              0x08

/* protos ****************************************************************/

static void setupRegisters (uint32_t blockNumber);
static void ataGetWord (uint8_t address, uint8_t *dataH, uint8_t *dataL);
static void ataPutWord (uint8_t address, uint8_t dataH, uint8_t dataL);
static void waitWhileDisk (uint8_t mask, bool_t cond);

/* variables *************************************************************/

block_t totalDiskSize;

/* functions *************************************************************/

inline extern bool_t ataInit (void) {
  bool_t lba_mode = 0;

  /* init disk */
  ataPutWord (ATA_REG_LBA3, 0x00, 0xa0);
  waitWhileDisk (STATUS_DRDY, FALSE);

  /* set drive information command */
  waitWhileDisk (STATUS_BSY, STATUS_BSY);
  ataPutWord (ATA_REG_COMMAND, 0x00, ATA_CMD_IDENTIFY_DRIVE);
  waitWhileDisk (STATUS_DRQ, FALSE);

  { /* read information bytes from disk */
    uint8_t i;
    uint8_t msb;
    uint8_t lsb;

    for (i = 0; i <= 61; i++) {
      ataGetWord (ATA_REG_DATA, &msb, &lsb);

      if (i == 49) {
        lba_mode = msb & 0x02;
      } else if (i == 60) {
        *((uint8_t *)(&totalDiskSize) + 0) = lsb;
        *((uint8_t *)(&totalDiskSize) + 1) = msb;
      } else if (i == 61) {
        *((uint8_t *)(&totalDiskSize) + 2) = lsb;
        *((uint8_t *)(&totalDiskSize) + 3) = msb;
      }
    }
  }

  /* not successful if drive don't use LBA */
  return lba_mode;
}

void ataGetBlock (block_t blockNumber, uint8_t *block) {

 bufferSize_t byteNumber;

  setupRegisters (blockNumber);

  /* write command */
  ataPutWord (ATA_REG_COMMAND, 0x00, ATA_CMD_READ_SECT);

  waitWhileDisk (STATUS_DRQ, FALSE);
  /* TODO: why is the following necessary? Without it, some blocks
     don't load correctly! */
  waitWhileDisk (STATUS_BSY, STATUS_BSY); 

  /* collect all the bytes */
  for (byteNumber = 0; byteNumber < BLOCKSIZE; byteNumber += 2) {
    ataGetWord (ATA_REG_DATA, &block[byteNumber + 1], &block[byteNumber]);
  }
}

void ataPutBlock (block_t blockNumber, uint8_t *block) {
  bufferSize_t byteNumber;
  
  setupRegisters (blockNumber);

  /* write command */
  ataPutWord (ATA_REG_COMMAND, 0x00, ATA_CMD_WRITE_SECT);

  waitWhileDisk (STATUS_DRQ, FALSE);
  /* TODO: is the following necessary? */
  waitWhileDisk (STATUS_BSY, STATUS_BSY); 
  
  /* write all the bytes */
  for (byteNumber = 0; byteNumber < BLOCKSIZE; byteNumber += 2) {
    ataPutWord (ATA_REG_DATA, block[byteNumber + 1], block[byteNumber]);
  }
}

static void setupRegisters (uint32_t blockNumber) {
  waitWhileDisk (STATUS_BSY, STATUS_BSY);

  /* init registers */
  ataPutWord (ATA_REG_SECTORS, 0x00, 0x01);
  ataPutWord (ATA_REG_LBA0, 0x00, blockNumber);
  ataPutWord (ATA_REG_LBA1, 0x00, blockNumber >> 8);
  ataPutWord (ATA_REG_LBA2, 0x00, blockNumber >> 16);
  ataPutWord (ATA_REG_LBA3, 0x00, 0xe0 | ((blockNumber >> 24) & 0x0f));
}

static void ataGetWord (uint8_t address, uint8_t *dataH, uint8_t *dataL) {
  /* to make sure variables are not in external SRAM */
  	uint8_t h, l; 

  /* disable interrupts */
  	cli();
  /* set up address */
#ifdef OLD_BOARD
   	
	outp ((address & 0xf8) | (inp (PORTB) & 0x07), PORTB);
#endif
#ifdef ATA_ADDRESSLATCH // FOR TXRX

	PORTD = (PORTD & 0xC4) | ((address & 0x1C) <<1);// FOR TXRX
#endif
#ifdef NEW_BOARD

	PORTD = (PORTD & 0xC4) | (address & 0x03) | ((address & 0x1C) <<1);
#endif

  /* disable external SRAM */
  	cbi (MCUCR, SRE);
  
#ifdef ATA_ADDRESSLATCH // FOR TXRX
	/* set up rest of address if lines are connected to latch */
	DDRA = 0xff;// #Port a out
	PORTA = (address & 0x03);// put bit 0,1 to Port
	sbi (PORT_ALE, BIT_ALE);// set Ale to activate ladge
	cbi (PORT_ALE, BIT_ALE);// clr Ale to mak it save
#endif

  /* set ATA databus to input */
	outp (0x00, DDRA);
	outp (0x00, DDRC);
  /* disable pullups */
	outp (0x00, PORTA);
	outp (0x00, PORTC);
  /* assert DIOR */
  	cbi (PORTB, ATA_DIOR);
  /* wait a short time */
  	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
  /* collect data */
	l = inp (PINA);
	h = inp (PINC);
  /* reset DIOR*/
	sbi (PORTB, ATA_DIOR);
  /* enable external SRAM */
	sbi (MCUCR, SRE);
  /* copy to parameters */
  	*dataH = h;
	*dataL = l;
  /* enable interrupts */
  sei();
}

static void ataPutWord (uint8_t address, uint8_t dataH, uint8_t dataL) {
  /* disable interrupts */
  cli();
  /* set up address */
#ifdef OLD_BOARD

	outp ((address & 0xf8) | (inp (PORTB) & 0x07), PORTB);
#endif
#ifdef ATA_ADDRESSLATCH// FOR TXRX

	PORTD = (PORTD & 0xC4) | ((address & 0x1C) <<1);// FOR TXRX
#endif
#ifdef NEW_BOARD

	PORTD = (PORTD & 0xC4) | (address & 0x03) | ((address & 0x1C) <<1);
#endif

  /* set ATA databus to output */
	DDRA = 0xff;
	DDRC = 0xff;
  /* disable external SRAM */
  cbi (MCUCR, SRE);
#ifdef ATA_ADDRESSLATCH  // FOR TXRX
	/* set up rest of address if lines are connected to latch */
	PORTA = (address & 0x03);// FOR TXRX
	sbi (PORT_ALE, BIT_ALE);// FOR TXRX
	cbi (PORT_ALE, BIT_ALE);// FOR TXRX
#endif
	/* wait a short time */
	asm volatile ("nop");
	/* assert DIOW */
	cbi (PORTB, ATA_DIOW);
	/* wait a short time */
	asm volatile ("nop");
	/* put data on bus */
	outp (dataL, PORTA);
	outp (dataH, PORTC);
	/* reset DIOW*/
	sbi (PORTB, ATA_DIOW);
	/* enable external SRAM */
	sbi (MCUCR, SRE);
	/* enable interrupts */
  sei();
}

static void waitWhileDisk (uint8_t mask, bool_t cond) {
  uint8_t status;
  uint8_t dummy;
  
  do {
    ataGetWord (ATA_REG_COMMAND, &dummy, &status);
  } while ((status & mask) == cond);
}