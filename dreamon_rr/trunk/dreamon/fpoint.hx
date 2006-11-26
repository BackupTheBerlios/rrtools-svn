/***************************************************************************
 *   Copyright (C) 2000 - 2006 by Christoph Thelen                         *
 *   DocBacardi@the-dreams.de                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*-----------------------------------*/

FPointTempTyp		= $01		; Long (2)
FPointTempFlag		= $40
FPointTraceTyp		= $01		; Long (2)
FPointDisable		= $80

FPointFlag_CmpErr       = $80

FPointMode_Normal	= 0



FPRamRom_Ram		= 0
FPRamRom_Rom		= 1
FPRamRom_IO		= 2
FPRamRom_Err		= $ff

/*-------------------------------------
 FPEntry
-------------------------------------*/

			.STRUCT
FPE_Adr			.SLONG
FPE_Typ			.SBYTE	;BCJL
FPE_Len			.SBYTE
FPE_Mode	        .SBYTE	;NCAR
FPE_RamRom		.SBYTE
FPE_Flags		.SBYTE
FPE_Par			.SBYTE
FPE_Restore		.SAREA(4)
FPE_len			.SLEN

/*-------------------------------------
 Shared with Relocate from Zp0 on
-------------------------------------*/

	.segment "zeropage"

FPointZp_Cnt		.DB 0
FPointZp_RemoteFlags	.DB 0			;Muss dahinter sein, da mit A16 kopiert wird

FPointZp_Zp0		.DB 0
FPointZp_Zp1		.DB 0

FPointZp_DZp0		.DB 0
FPointZp_DZp1		.DB 0
FPointZp_DAdr0		.DSB 3
FPointZp_DAdr1		.DW 0

FPointZp_Act		.DSB FPE_len
FPointZp_Temp		.DSB FPE_len		;Used in Opcodes

/*-----------------------------------*/

