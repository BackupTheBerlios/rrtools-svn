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

ErrNo_IEC_Write         = %00000001
ErrNo_IEC_Read          = %00000010
ErrNo_IEC_EOF           = %01000000
ErrNo_IEC_DevNPresent   = %10000000

;--------------------------------------
; Kombiniere die Errorcodes von 'DLoad_Install'
; mit 'FileNotFound' und 'ReadError'

SpeederError_FileNotFound	= 0
SpeederError_ReadError		= 5

;--------------------------------------

	.segment "zeropage"

FileZp_Device		.DB 0
FileZp_SecAdr		.DB 0
FileZp_NameLen		.DB 0
FileZp_NamePtr		.DW 0
FileZp_RelocAdr		.DSB 3
FileZp_BlockSize = FileZp_RelocAdr
FileZp_SaveFrom		.DSB 3
FileZp_SaveTo		.DSB 3
FileZp_WhereToLoad	.DB 0

FileZp_94		.DB 0
FileZp_95		.DB 0
FileZp_A3		.DB 0
FileZp_A5		.DB 0
FileZp_90		.DB 0

LdBfZp_Len		.DB 0

;--------------------------------------

