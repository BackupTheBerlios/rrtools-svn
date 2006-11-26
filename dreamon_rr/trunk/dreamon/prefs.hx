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
; only temp used in Prefs
;--------------------------------------

	.segment "zeropage"

PrefsZp_Pad1		= ZpSlot0	;.DW 0		;Pad1 muss direkt vor Pad2 sein!
PrefsZp_Pad2		= ZpSlot0+2	;.DB 0		;Pad2 muss direkt hinter Pad1 sein!
PrefsZp_ModeNr		= ZpSlot0+3	;.DB 0
PrefsZp_Ptr0		= ZpSlot0+4	;.DW 0
PrefsZp_Y		= ZpSlot0+6	;.DB 0

;--------------------------------------

	.segment "bss"

PrefsBSS_PaletteZp		.DSB Palette_len

;--------------------------------------
