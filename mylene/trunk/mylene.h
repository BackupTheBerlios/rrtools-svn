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

	.segment "zp"

LevelTable			.DW 0
LevelPtr			.DW 0

ListOutZp_Line			.DB 0
ListOutZp_StartPtr		.DW 0
ListOutZp_TmpPtr		.DW 0

BarPtr				.DW 0
BarCrsrPos			.DB 0

LevelBuf			.DSB level_entry_size
LevelAction			.DSB level_action_size

;--------------------------------------

	.segment "data"

LoadZp_Cnt			.DW 0

GotoLevel_Flag			.DB 0		; zp for GotoLevel
GotoLevel_Level			.DB 0		; zp for GotoLevel
GotoLevel_LastType		.DB 0

Entry_LastTyp			.DB 0

Level				.DB 0
LevelMax			.DB 0
Level0Init			.DW 0

MovePrevCache_LastHeader	.DW 0

;--------------------------------------
