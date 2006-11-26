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

MathOp_Plus		= 0
MathOp_Minus		= 1
MathOp_Mult		= 2
MathOp_Div		= 3
MathOp_ShiftL		= 4
MathOp_ShiftR		= 5
MathOp_Lo		= 6
MathOp_Hi		= 7
MathOp_Bank		= 8
MathOp_Not		= 9
MathOp_And		= 10
MathOp_Or		= 11
MathOp_Eor		= 12
MathOp_Modulo		= 13

MathOp_KlAuf		= 14
MathOp_KlZu		= 15

;--------------------------------------

	.segment "zeropage"

GetNumZp_DefaultSystem	.DB 0
GetNumZp_ArgLen		.DB 0
GetNumZp_LastOkPos	.DB 0

GetNumZp_StartBra	.DB 0
GetNumZp_EndBra		.DB 0
GetNumZp_Solves		.DB 0

GetNumZp_OpCnt		.DB 0

GetNumZp_Val1		.DSB 4
GetNumZp_Val2		.DSB 4
GetNumZp_Val3		.DSB 4
GetNumZp_System		.DB 0
GetNumZp_Digits		.DB 0
GetNumZp_MaxDigits	.DB 0

;--------------------------------------

