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

KeyBFlag_KeyNrm		= %01000000		;Normal Key Pressed
KeyBFlag_KeySpi		= %10000000		;Special Key Pressed
KeyBFlag_Stop		= %00000001		;Stop Pressed
KeyBFlag_NoScroll	= %00000010		;NoScroll activated

/*-----------------------------------*/

	.segment "zeropage"

KeyBZp_Attr		.DB 0
KeyBZp_Qualifier	.DB 0
KeyBZp_Pressed		.DB 0
KeyBZp_RepeatCnt	.DB 0
KeyBZp_RepeatVal	.DB 0
KeyBZp_InitRepeatVal	.DB 0
KeyBZp_Key		.DB 0
KeyBZp_Flag		.DB 0
KeyBZp_Ptr		.DW 0

/*-----------------------------------*/




