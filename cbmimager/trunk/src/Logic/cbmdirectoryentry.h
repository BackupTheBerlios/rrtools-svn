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

#include "cbmsector.h"
#include "imagebase.h"

#include <string.h>
#include <memory.h>

#include "wx/wx.h"



typedef enum CBMFileType
{
	CBM_DEL = 0,
	CBM_SEQ = 1,
	CBM_PRG = 2,
	CBM_USR = 3,
	CBM_REL = 4,
	CBM_DIR = 6,
	CBM_PROTECTED = 0x40,
	CBM_CLOSED = 0x80
};



// Contains Information about a Directory-Entry
class CCbmDirectoryEntry
{
public:
	~CCbmDirectoryEntry(void);

	// Creates an empty Directory-Entry
	CCbmDirectoryEntry();

	/// <summary>
	/// Creates a new DirectoryEntry from Sector-Data at the specified offset
	/// </summary>
	/// <param name="sectorData">Raw Sector-Data (265 bytes)</param>
	/// <param name="startOffset">Offset in the Sector-Data, where the Directory-Entry starts</param>
	CCbmDirectoryEntry(CCbmImageBase *image, CCbmSector *sectorData, int startOffset);

	void SetFileType(byte type);

	/// <summary>
	/// Writes the DirectoryEntry back to the Image
	/// </summary>
	/// <param name="image"></param>
	void Write(CCbmImageBase *image);

	/// <summary>
	/// Deletes the File associated with the current Directory Entry
	/// </summary>
	/// <param name="image">The Image in where the Directory Entry resists</param>
	void DeleteFile(CCbmImageBase *image);

	// Reads the file to a buffer. The caller must delete the buffer, when it's not longer used !
	int GetFileContent(CCbmImageBase *image, byte **buffer);

	// Overwrites the contents of the file with the supplied Data. The data should have been retrieved with "GetFileContent()"
	void OverwriteFileContent(CCbmImageBase *image, byte *buffer);

	char* GetFileTypeString();

	CBMFileType GetFileType();

	unsigned char *GetFileName();

	void SetFileName(unsigned char *value);

	/// <summary>
	/// First Track of the file
	/// </summary>
	int GetFileStartTrack();

	void SetFileStartTrack(int value);

	/// <summary>
	/// First Sector of the File
	/// </summary>
	int GetFileStartSector();

	void SetFileStartSector(int value);

	// Track of this Directory Entry
	int GetDirTrack();

	// Sector of this Directory Entry
	int GetDirSector();

	// Offset in the Directory-Sector, where this Entry starts
	int GetEntryOffset();

	int GetBlocksUsed();
	int GetBlocksUsedReal();

	void SetBlocksUsed(int value);

	bool GetClosedProperly();
	void SetClosedProperly(bool value);

	bool GetScratchProtected();
	void SetScratchProtected(bool value);

	int GetEntryIndex();

	void SetEntryIndex(int index);

	/// <summary>
	/// Offset in the D64 Image, where the current Entry begins
	/// </summary>
	int GetImageOffset();

	void SetImageOffset(int value);

	// Allows moving the Entry in the specified Image to the specified position
	void SetImageOffset(CCbmImageBase *diskImage, int dirTrack, int dirSector, int entryOffset);

	bool WasCircularLinked();

	bool HasBadSectors();

	wxString GetErrorDescription();

private:
	void Init(void);

	CCbmImageBase *diskImage;
	char* fileType;
	byte typeCode;
	bool closedProperly;
	bool scratchProtected;
	bool circularLinked;
	bool hasBadSectors;
	wxString errorDescription;		// contains a description, if an error in the entry was encountered
	int offsetInImage;				// Offset in the D64 Image, where the current Entry begins
	int startTrack, startSector;	// Track / Sector of File
	int dirTrack, dirSector;		// Track / Sector of the Directory, where this entry resides
	int entryStartOffset;			// Start of this Entry in the Directory Sector
	int entryIndex;					// Index of this Entry in the Directory
	unsigned char fileName[17];
	int blocksUsed;					// the reported number of blocks for this file
	int blocksUsedReal;				// the real number of used blocks
};
