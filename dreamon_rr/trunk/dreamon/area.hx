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
;only temp used in Area.src
;--------------------------------------

	.segment "zeropage"

AreaZp_BlkLen	= ZpSlot0		;.DB 0
AreaZp_Zp0	= ZpSlot0+1	;.DB 0
AreaZp_Ptr0	= ZpSlot0+2	;.DW 0

GetHZp_Mode	= ZpSlot0+4	;.DB 0
GetHZp_Sys	= ZpSlot0+5	;.DB 0
GetHZp_Numb	= ZpSlot0+6	;.DSB 3
GetHZp_Mask	= ZpSlot0+9	;.DSB 3

;--------------------------------------
