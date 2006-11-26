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

OptionFlag_FollowXep	= %00000001	;rep & sep change RegLen while DisAss?
OptionFlag_Verbose	= %00000010     ;Show Adress or Difference/Disass for C/O
OptionFlag_MMap		= %00000100	;Map Memory to original State
OptionFlag_Speeder	= %00001000	;Try to use Speeder

;--------------------------------------

InitErr_CodeChkSum	= 1
InitErr_UnknownFP	= 2
InitErr_StrBufChkSum	= 4

;--------------------------------------

	.segment "zeropage"

Adress			.DSB 3

CmdLineLen		.DB 0
CmdLinePos		.DB 0
CmdCursorXPos		.DB 0

ConvertFlag		.DB 0
ReMemDumpPos		.DB 0

FillBufLen		.DB 0

OptionFlags		.DB 0

Intern_01		.DB 0
Intern_MX		.DB 0

CRTRamZp_SrcAdr		.DW 0
CRTRamZp_Adress		.DW 0
CRTRamZp_Zp0		.DB 0
CRTRamZp_Length		.DB 0
CRTRamZp_SegSize	.DB 0

;StringBufZp is static global
StringBufZp_Start	.DW 0
StringBufZp_FKeysEnd	.DW 0
StringBufZp_LabelsEnd	.DW 0
StringBufZp_TempEnd	.DW 0
StringBufZp_End		.DW 0

NextCmdCharZp_Y		.DB 0

CopyCRTZp_Src		.DW 0
CopyCRTZp_Dst		.DW 0
CopyCRTZp_Len		.DW 0
CopyCRTZp_SegSize	.DW 0

ZpSlot0			.DSB 11

;Nur temporaer in FKeys benoetigt
FKeysZp_Key		= ZpSlot0	;ZBYTE
FKeysZp_Flags		= ZpSlot0+1	;ZBYTE
FKeysZp_Nr		= ZpSlot0+2	;ZBYTE
FKeysZp_CopyPtr		= ZpSlot0+3	;ZWORD
FKeysZp_FKeyAdr		= ZpSlot0+5	;ZWORD
StringBufZp_TmpLen	= ZpSlot0+7	;ZWORD
StringBufZp_TmpOver	= ZpSlot0+9	;ZWORD

;Nur temporaer in GetNum benoetigt
LabelZp_NameStart	= ZpSlot0	;ZBYTE
LabelZp_NameEnd		= ZpSlot0+1	;ZBYTE
LabelZp_NameLen		= ZpSlot0+2	;ZBYTE
LabelZp_ValueLen	= ZpSlot0+3	;ZBYTE
LabelZp_MovePtr0	= ZpSlot0+4	;ZWORD
LabelZp_MovePtr1	= ZpSlot0+6	;ZWORD
LabelZp_MoveLen0	= ZpSlot0+8	;ZBYTE
LabelZp_MoveLen1	= ZpSlot0+9	;ZBYTE

;Nur temporaer in YesNo Routine benoetigt
YesNoZp0		= ZpSlot0	;ZBYTE
YesNoZp1		= ZpSlot0+1	;ZBYTE

;--------------------------------------


