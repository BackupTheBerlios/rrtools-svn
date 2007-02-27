/***************************************************************************
 *   Copyright (C) 2006 by T.Terhaar and C. Thelen                         *
 *   uncletom@users.berlios.de, baccy_drm@users.berlios.de                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <stdlib.h>
#include <memory.h>

#include "wx/wx.h"


typedef unsigned char byte;


typedef struct _T64Header
{
	char description[32];
	byte Version[2];
	unsigned short MaxFiles;
	unsigned short CurrFiles;
	byte Reserved[2];
	char UserDescr[24];
} T64Header;

typedef struct _T64FileEntry
{
	byte EntryUsed;
	byte FileType;
	unsigned short StartAddr;
	unsigned short EndAddr;
	byte ReservedA[2];
	int TapePos;
	byte ReservedB[4];
	char FileName[16];
} T64FileEntry;




class CT64Reader
{
public:
	CT64Reader(void);
	~CT64Reader(void);

	// Read files from the tape-image and create Pxx Files in temp-dir, return number of extracted files
	int Read(wxString filename);
	// Get the name of an extracted file; number ranges from 0 to the number returned by Read()
	wxString &GetExtractedFileName(int number) const;

private:
	_T64Header fileHeader;
	_T64FileEntry *fileEntries;
	byte *buffer;
	wxArrayString filenames;
};
