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
  dos-init.c V1.32
  Contains the initialization, formatting and free block management
  code for the file system
*/

/* protos ****************************************************************/

/* variables *************************************************************/

/* functions *************************************************************/
    
	inline extern bool_t memread (struct channelTableStruct *channel) {
  uint8_t *buffer = channel->buffer;

  /* error number */
  *(buffer++) = (error >> 4) | '0';
  *(buffer++) = (error & 0x0f) | '0';
	return FALSE;
  }

  