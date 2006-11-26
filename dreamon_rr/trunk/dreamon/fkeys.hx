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

	.segment "bss"

FKeysBSS_MacroStackPos	.DB 0
FKeysBSS_MacroStackNr	.DSB 16
FKeysBSS_MacroStackLo	.DSB 16
FKeysBSS_MacroStackHi	.DSB 16
FKeysBSS_RecordKey	.DB 0
FKeysBSS_OldKeyLen	.DW 0
FKeysBSS_Flags		.DB 0
FKeysBSS_RecFlags	.DB 0

;--------------------------------------

