/***************************************************************************
 *   Copyright (C) 2002, 2003, 2004, 2005, 2006 by Christoph Thelen        *
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

#ifndef __MAIN_H__
#define __MAIN_H__

#include <errno.h>
#include <stdio.h>

extern bool cfg_verbose;
extern bool cfg_debug;
extern long cfg_warnflags;
extern bool cfg_allowSimpleRedefine;

extern uint32_t cfg_maxwarnings;
extern uint32_t cfg_maxerrors;

extern FILE *debugLog;

extern stringsize_t **includePaths;
extern stringsize_t includeMaxLen;
extern includePathscnt_t includePaths_count;


#endif		/* __MAIN_H__ */
