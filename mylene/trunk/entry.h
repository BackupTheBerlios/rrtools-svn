/***************************************************************************
 *   Copyright (C) 1998 - 2006 by Christoph Thelen                         *
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

DirHFlag_NoHeadLine	= %00000001
DirHFlag_NoBFreeLine	= %00000010

;--------------------------------------

;DirH		STRUCT
DirH_Prev	= $00	; word
DirH_Last	= $02	; word
DirH_Flags	= $04	; byte
DirH_Level	= $05	; byte
DirH_Typ	= $06	; byte
DirH_len	= $07

;DirE		STRUCT
DirE_Blocks		= $00	; word
DirE_Name		= $02	; $18 bytes (2 quotes, 16 name, 1 space, 1 protect, 3 type, 1closed)
DirE_Ptr		= $1a	; word
DirE_Typ		= $1c	; byte
DirE_Color		= $1d	; byte
DirE_ActionIdx		= $1e	; byte
DirE_UserData		= $1f	; word
DirE_len	= $21

;--------------------------------------

	.segment "zp"

EntryZp_ListEnd		.DW 0
EntryZp_MemEnd		.DW 0
EntryZp_ActHeader	.DW 0
EntryZp_ActEntry	.DW 0
EntryZp_HeadPtr		.DW 0
EntryZp_FirstPtr	.DW 0
EntryZp_LastPtr		.DW 0
EntryZp_BFreePtr	.DW 0

EntryZp_FirstScrlLine	.DB 0
EntryZp_LastScrlLine	.DB 0

;--------------------------------------

	.segment "data"

Entry_EBuf		.DSB DirE_len
EntryZp_HBuf		.DSB DirH_len

;--------------------------------------

