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

#include "cbmdirectoryentry.h"

#include "wx/wx.h"


WX_DEFINE_ARRAY(unsigned long, FileSectors);



CCbmDirectoryEntry::~CCbmDirectoryEntry(void)
{
}


// Creates an empty Directory-Entry
CCbmDirectoryEntry::CCbmDirectoryEntry()
{
	Init();
}


/// <summary>
/// Creates a new DirectoryEntry from Sector-Data at the specified offset
/// </summary>
/// <param name="sectorData">Raw Sector-Data (265 bytes)</param>
/// <param name="startOffset">Offset in the Sector-Data, where the Directory-Entry starts</param>
CCbmDirectoryEntry::CCbmDirectoryEntry(CCbmImageBase *image, CCbmSector *sectorData, int startOffset)
{
	int track, sector, lastTrack = 0, lastSector = 0;
	bool cont = true;
	int offset, lastValidOffset = -1;

	Init();

	diskImage = image;
	dirTrack = sectorData->GetTrack();
	dirSector = sectorData->GetSector();
	entryStartOffset = startOffset;
	offsetInImage = diskImage->GetSectorOffset(dirTrack, dirSector) + startOffset;

	byte type = sectorData->GetRawSector()[startOffset];
	SetFileType(type);
	startTrack = sectorData->GetRawSector()[startOffset + 1];
	startSector = sectorData->GetRawSector()[startOffset + 2];
	blocksUsed = sectorData->GetRawSector()[startOffset + 28] + (sectorData->GetRawSector()[startOffset + 29] << 8);
	memcpy(fileName, sectorData->GetRawSector() + startOffset + 3, 16);
	fileName[16] = 0;

	// Get "real" number of used blocks by traversing the file-sectors
	track = startTrack;
	sector = startSector;
	blocksUsedReal = 0;

	FileSectors sectorArray;
	while (track > 0 && cont)
	{
		sectorArray.Add((track << 16) + sector);
		try
		{
			offset = image->GetSectorOffset(track, sector);
		}
		catch (char*)
		{
			if (track == startTrack && sector == startSector)							// first link illegal ?
			{
				image->GetHeaderInfo(NULL, NULL, &startTrack, &startSector);			// set to directory-start
				image->GetRawImage()[offsetInImage + 1] = (unsigned char)startTrack;
				image->GetRawImage()[offsetInImage + 2] = (unsigned char)startSector;
				errorDescription.Printf(wxT("First Track/Sector changed to %d/%d"), startTrack, startSector);
			}
			hasBadSectors = true;
			blocksUsedReal = 0;
			if (lastValidOffset >= 0)
			{
				image->GetRawImage()[lastValidOffset + 0] = 0;
				image->GetRawImage()[lastValidOffset + 1] = 255;						// "repair" link
				errorDescription.Printf(wxT("Link at %d/%d (pointing to %d/%d) changed to 0/255"), lastTrack, lastSector, track, sector);
			}
			return;
		}
		lastTrack = track;
		lastSector = sector;
		lastValidOffset = offset;														// remember last valid offset
		track =  image->GetRawImage()[offset + 0];										// (points to last valid Track/Sector in image)
		sector = image->GetRawImage()[offset + 1];
		if (sectorArray.Index((track << 16) + sector) != wxNOT_FOUND)					// circular link encountered
		{
			cont = false;
			circularLinked = true;					// mark file as bad
			// Fix the Link to prevent freezing when deleting or extracting the file
			image->GetRawImage()[offset + 0] = 0;	// next Track
			image->GetRawImage()[offset + 1] = 255; // next Sector
			errorDescription.Printf(wxT("Link at %d/%d (pointing to %d/%d) changed to 0/255"), lastTrack, lastSector, track, sector);
		}
		blocksUsedReal++;
	}
}


void CCbmDirectoryEntry::Init(void)
{
	blocksUsed = 0;
	blocksUsedReal = 0;
	dirSector = startSector = 255;
	dirTrack = startTrack = 0;
	closedProperly = true;
	scratchProtected = false;
	circularLinked = false;
	hasBadSectors = false;
	fileType = NULL;
	fileName[0] = 0;

	entryIndex = -1;
	entryStartOffset = -1;
	offsetInImage = 0;
	typeCode = 0;
}


void CCbmDirectoryEntry::SetFileType(byte type)
{
	typeCode = type;
	switch (typeCode & 15)
	{
		case 0:
			fileType = "DEL";
			break;
		case 1:
			fileType = "SEQ";
			break;
		case 2:
			fileType = "PRG";
			break;
		case 3:
			fileType = "USR";
			break;
		case 4:
			fileType = "REL";
			break;
		case 6:
			fileType = "DIR";
			break;
		default:
			fileType = "?< ";
			break;
	}
	closedProperly = (typeCode & CBM_CLOSED) != 0;
	scratchProtected = (typeCode & CBM_PROTECTED) != 0;
}


/// <summary>
/// Writes the DirectoryEntry back to the Image
/// </summary>
/// <param name="image"></param>
void CCbmDirectoryEntry::Write(CCbmImageBase *image)
{
	if (offsetInImage == 0)
	{
		throw "Must set ImageOffset first !";
	}

	image->GetRawImage()[offsetInImage] = typeCode;							// File Type
	image->GetRawImage()[offsetInImage + 1] = (byte)startTrack;
	image->GetRawImage()[offsetInImage + 2] = (byte)startSector;			// Start of File

	memcpy(image->GetRawImage() + offsetInImage + 3, fileName, 16);

	image->GetRawImage()[offsetInImage + 28] = (byte)(blocksUsed & 255);
	image->GetRawImage()[offsetInImage + 29] = (byte)(blocksUsed >> 8);		// set used blocks
	// If type is Directory, set name also for the Header-Block
	if (GetFileType() == CBM_DIR)
	{
		CCbmSector *sec = image->GetSector(startTrack, startSector);
		memcpy(sec->GetRawSector() + 0x90, fileName, 16);
		image->WriteSector(sec);
		delete sec;
	}
}

/// <summary>
/// Deletes the File associated with the current Directory Entry
/// </summary>
/// <param name="image">The Image in where the Directory Entry resists</param>
void CCbmDirectoryEntry::DeleteFile(CCbmImageBase *image)
{
	if (offsetInImage == 0)
	{
		throw "Must set ImageOffset first !";
	}

	int track = startTrack;
	int sector = startSector;
	while (track != 0)
	{
		CCbmSector *sec = image->GetSector(track, sector);  // First Sector of file
		image->FreeSector(track, sector);					// Free Sector
		track = sec->GetNextTrack();
		sector = sec->GetNextSector();
		delete sec;
	}
	blocksUsed = 0;
	startTrack = 0;
	startSector = 255;
	SetFileType(CBM_DEL + CBM_CLOSED);
	memset(fileName, '-', 16);								// Set Filename to "----------------"
	Write(image);
}


int CCbmDirectoryEntry::GetFileContent(CCbmImageBase *image, byte **buffer)
{
	int sectorsRead = 0;
	int sectorSize = 254;
	int fileSize = 0;

	if (offsetInImage == 0)
	{
		throw "Must set ImageOffset first !";
	}

	*buffer = new byte[254 * blocksUsedReal];				// Allocate buffer (may be larger than needed)
	int track = startTrack;
	int sector = startSector;
	while (track != 0)
	{
		CCbmSector *sec = image->GetSector(track, sector);  // First Sector of file
		track = sec->GetNextTrack();
		sector = sec->GetNextSector();
		if (track != 0)
			sectorSize = 254;
		else
			sectorSize = sector - 1;
		memcpy(*buffer + (sectorsRead * 254), sec->GetRawSector() + 2, sectorSize);
		fileSize += sectorSize;
		sectorsRead++;
		delete sec;
	}

	return fileSize;
}


void CCbmDirectoryEntry::OverwriteFileContent(CCbmImageBase *image, byte *buffer)
{
	int sectorsWritten = 0;
	int sectorSize = 254;

	if (offsetInImage == 0)
	{
		throw "Must set ImageOffset first !";
	}

	int track = startTrack;
	int sector = startSector;
	while (track != 0)
	{
		CCbmSector *sec = image->GetSector(track, sector);  // First Sector of file
		track = sec->GetNextTrack();
		sector = sec->GetNextSector();
		if (track != 0)
			sectorSize = 254;
		else
			sectorSize = sector - 1;
		memcpy(sec->GetRawSector() + 2, buffer + (sectorsWritten * 254), sectorSize);
		image->WriteSector(sec);
		sectorsWritten++;
		delete sec;
	}
}


char* CCbmDirectoryEntry::GetFileTypeString()
{
	return fileType;
}

CBMFileType CCbmDirectoryEntry::GetFileType()
{
	return (CBMFileType)(typeCode & 15);
}

unsigned char *CCbmDirectoryEntry::GetFileName()
{
	return fileName;
}


void CCbmDirectoryEntry::SetFileName(unsigned char *value)
{
	int len = strlen((char*)value);
	if (len > 16)
		len = 16;

	if (value == NULL)
	{
		memset(fileName, 0xa0, len);
	}
	else
	{
		memcpy(fileName, value, len);		// TODO: Check length of value ?
	}
	memset(fileName + len, 0xa0, 16 - len); 
}

/// <summary>
/// First Track of the file
/// </summary>
int CCbmDirectoryEntry::GetFileStartTrack()
{
	return startTrack;
}


void CCbmDirectoryEntry::SetFileStartTrack(int value)
{
	startTrack = value;
}

/// <summary>
/// First Sector of the File
/// </summary>
int CCbmDirectoryEntry::GetFileStartSector()
{
	return startSector;
}

void CCbmDirectoryEntry::SetFileStartSector(int value)
{
	startSector = value;
}

// Track of this Directory Entry
int CCbmDirectoryEntry::GetDirTrack()
{
	return dirTrack;
}


// Sector of this Directory Entry
int CCbmDirectoryEntry::GetDirSector()
{
	return dirSector;
}


// Offset in the Directory-Sector, where this Entry starts
int CCbmDirectoryEntry::GetEntryOffset()
{
	return entryStartOffset;
}


int CCbmDirectoryEntry::GetBlocksUsed()
{
	return blocksUsed;
}

int CCbmDirectoryEntry::GetBlocksUsedReal()
{
	return blocksUsedReal;
}

void CCbmDirectoryEntry::SetBlocksUsed(int value)
{
	blocksUsed = value;
}

bool CCbmDirectoryEntry::GetClosedProperly()
{
	return closedProperly;
}

bool CCbmDirectoryEntry::GetScratchProtected()
{
	return scratchProtected;
}

void CCbmDirectoryEntry::SetClosedProperly(bool value)
{
	closedProperly = value;
}

void CCbmDirectoryEntry::SetScratchProtected(bool value)
{
	scratchProtected = value;
}


int CCbmDirectoryEntry::GetEntryIndex()
{
	return entryIndex;
}

void CCbmDirectoryEntry::SetEntryIndex(int index)
{
	entryIndex = index;
}


/// <summary>
/// Offset in the D64 Image, where the current Entry begins
/// </summary>
int CCbmDirectoryEntry::GetImageOffset()
{
	return offsetInImage;
}


void CCbmDirectoryEntry::SetImageOffset(int value)
{
	offsetInImage = value;
}


// Allows moving the Entry in the specified Image to the specified position
void CCbmDirectoryEntry::SetImageOffset(CCbmImageBase *diskImage, int dirTrack, int dirSector, int entryOffset)
{
	entryStartOffset = entryOffset;
	this->dirTrack = dirTrack;
	this->dirSector = dirSector;
	offsetInImage = diskImage->GetSectorOffset(dirTrack, dirSector) + entryOffset;
}


bool CCbmDirectoryEntry::WasCircularLinked()
{
	return circularLinked;
}


bool CCbmDirectoryEntry::HasBadSectors()
{
	return hasBadSectors;
}


wxString CCbmDirectoryEntry::GetErrorDescription()
{
	return errorDescription;
}

