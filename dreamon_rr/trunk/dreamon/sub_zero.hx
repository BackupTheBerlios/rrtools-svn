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

FreezeSource_Hard	= 0
FreezeSource_Soft	= 1

;--------------------------------------

;SubZero
			.STRUCT
SubZero_PC		.SWORD
SubZero_A		.SBYTE
SubZero_X		.SBYTE
SubZero_Y		.SBYTE
SubZero_StackPtr	.SBYTE
SubZero_Status		.SBYTE
SubZero_B		.SLEN
SubZero_01		.SBYTE
SubZero_len		.SLEN

;--------------------------------------

	.segment "zeropage"

SubZeroZp_Regs		.DSB SubZero_len
SubZeroZp_Source	.DB 0

;--------------------------------------
