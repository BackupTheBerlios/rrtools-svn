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

;--------------------------------------
;
;  CmdRange and Area
;
;--------------------------------------

RangeFlag_Up		= %01000000
RangeFlag_EndAdr	= %10000000
RangeFlag_SingleLine	= %00000100
RangeFlag_NonStop	= %00000001

;--------------------------------------

	.segment "zeropage"

RangeZp_Flags		.DB 0	;Flags (Up/Down...)
RangeZp_From		.DSB 3	;Start des Bereichs
RangeZp_To		.DSB 3	;Ende des Bereichs
RangeZp_With		.DSB 3	;Zielbereich
RangeZp_Len		.DSB 3	;Laenge From bis To
RangeZp_Cmd		.DB 0	;Routine (Disass, MemDump...)
RangeZp_Add		.DB 0	;Länge des Ausgegebenen

;--------------------------------------

