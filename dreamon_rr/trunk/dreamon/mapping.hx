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

MappingIdx_Mem0		= 0
MappingIdx_Mem1		= 1
MappingIdx_Mem2		= 2
MappingIdx_Mem3		= 3
MappingIdx_Mem4		= 4
MappingIdx_Mem5		= 5
MappingIdx_Mem6		= 6
MappingIdx_Mem7		= 7
MappingIdx_CrtRam0	= 8

;--------------------------------------

	.segment "zeropage"

MappingZp_Adress	.DSB 3
MappingZp_Y		.DB 0

;--------------------------------------
