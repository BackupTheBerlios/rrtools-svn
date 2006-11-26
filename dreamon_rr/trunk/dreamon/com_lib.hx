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

MaxScrDimX		= 80
MaxScrDimY		= 50

;--------------------------------------

;Palette
		        .STRUCT
Palette_Default		.SBYTE
Palette_Error		.SBYTE
Palette_Command		.SBYTE
Palette_Cursor		.SBYTE
Palette_SysTxt		.SBYTE
Palette_Adress		.SBYTE
Palette_DisAssBytes	.SBYTE
Palette_DisAssMne	.SBYTE
Palette_DisAssIll	.SBYTE
Palette_DisAssFPoint    .SBYTE
Palette_DumpBytes	.SBYTE
Palette_DumpSeperator	.SBYTE
Palette_DumpChars	.SBYTE
Palette_len		.SLEN

;--------------------------------------

	.segment "zeropage"

ComLibZp_CursorXPos	.DB 0
ComLibZp_CursorYPos	.DB 0
ComLibZp_CursorMaxXPos	.DB 0
ComLibZp_CursorMaxYPos	.DB 0
ComLibZp_Color		.DB 0
ComLibZp_CursorPtr	.DW 0
ComLibZp_CursorColPtr	.DW 0

ComLibZp_CursorMinLines	.DB 0
ComLibZp_CursorMaxLines	.DB 0

ComLibZp_RedirOutput	.DB 0
ComLibZp_RedirCPos	.DB 0

ComLibZp_StringPtr      .DSB 3
ComLibZp_StringFlag	.DB 0

ComLibZp_ScrollLen	.DW 0
ComLibZp_KeyZp	        .DB 0

ComLibZp_XSave		.DB 0

;--------------------------------------

ComLibZp_BlinkPtr	.DW 0
ComLibZp_BlinkColPtr	.DW 0
ComLibZp_CrsrFlag	.DB 0
ComLibZp_CrsrBlink	.DB 0
ComLibZp_CrsrBlinkCnt	.DB 0
ComLibZp_CrsrBlinkVal	.DB 0
ComLibZp_CrsrStoreChar	.DB 0
ComLibZp_CrsrStoreCol	.DB 0

ComLibZp_VICAttrib	.DB 0
ComLibZp_VDCAttrib	= ComLibZp_VICAttrib
ComLibZp_PrAttrib	= ComLibZp_VICAttrib

ComLibZp_VICLineAPtr	.DW 0
ComLibZp_VICLineBPtr	.DW 0
ComLibZp_VDCVPos	= ComLibZp_VICLineAPtr
ComLibZp_VDCXSave	= ComLibZp_VICLineAPtr+1
ComLibZp_VDCYSave	= ComLibZp_VICLineBPtr


ComLibZp_PrinterRevMode	.DB 0

;--------------------------------------

	.segment "bss"

ComLib_LineConnect	.DSB MaxScrDimY

ComLib_ScrPosLo		.DSB MaxScrDimY
ComLib_ScrPosMi		.DSB MaxScrDimY

;--------------------------------------

