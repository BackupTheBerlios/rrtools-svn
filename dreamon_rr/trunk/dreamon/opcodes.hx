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
; () Br
; [] EBr
; ,  C
; #  R
;--------------------------------------

AdrModeNone		= $0		;-
AdrModeRZp		= $1		;#Zp
AdrModeZp		= $2		;Zp
AdrModeBrZpCxBr		= $3		;(Zp,x)
AdrModeBrZpBrCy		= $4		;(Zp),y
AdrModeAbs		= $5		;Abs
AdrModeBrAbsBr		= $6		;(Abs)
AdrModeRel		= $7		;Rel
AdrModeZpCx		= $8		;Zp,x
AdrModeZpCy		= $9		;Zp,y
AdrModeAbsCx		= $a		;Abs,x
AdrModeAbsCy		= $b		;Abs,y

;--------------------------------------

	.segment "zeropage"

OpcodeZp_Adr		.DSB 3		;Adress to Disass
OpcodeZp_Copy		.DSB 4		;Copy of the 4 Bytes at Adr
OpcodeZp_Len		.DB 0		;1-4 Byte Command

OpcodeZp_AdrMode	.DB 0		;Pointer to AdrFlagTab
OpcodeZp_Offset		.DB 0		;Which Mne
OpcodeZp_Row	        .DB 0		;Mne and #$e0 / 16

OpcodeZp_Zp0		.DB 0
OpcodeZp_Zp1		.DB 0

;--------------------------------------

	.segment "bss"

DisAssDivePtr		.DB 0
DisAssDiveBuf		.DSB $ff

;--------------------------------------

PO0 = $00
PO1 = $07
PO2 = $15
PO3 = $17
PO4 = $1a
PO5 = $1b
PO6 = $1c
PO7 = $1d
PO8 = $1e
PO9 = $1f

;--------------------------------------

