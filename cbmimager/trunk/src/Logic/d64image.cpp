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

#include "d64image.h"

#include <string.h>

#include "wx/wx.h"
#include "wx/ffile.h"


CD64Image::CD64Image(void) : CCbmImageBase()
{
	unsigned char buffer[17];
	struct
	{
		int TrackStart, TrackEnd, NumSectors;
	} trackInfo[] = 
	{
		{1, 17, 21},
		{18, 24, 19},
		{25, 30, 18},
		{31, 35, 17}
	};

	imageType = D64;
	image = new byte[D64_IMAGE_LENGTH];
	memset(image, 0, D64_IMAGE_LENGTH);
	imageLength = D64_IMAGE_LENGTH;
	lastTrack = 35;
	// Create BAM
	bam = GetSector(18, 0);
	bam->SetNextTrack(18);
	bam->SetNextSector(1);
	bam->GetRawSector()[2] = 0x41;			// Formatcharacter "A"
	SetDiskName(CCbmImageBase::ASCII2PET("NEW DISK        ", 16, buffer));	// name must be 16 chars
	SetDiskID(CCbmImageBase::ASCII2PET("UT 2A", 5, buffer));				// set Name and ID (also saves the BAM)
	// Clear image by freeing all sectors
	for (int i = 0; i < 4; i++)
	{
		for (int track = trackInfo[i].TrackStart; track <= trackInfo[i].TrackEnd; track++)
		{
			if (track == 18)
				continue;
			for (int sector = 0; sector < trackInfo[i].NumSectors; sector++)
				FreeSector(track, sector);
		}
	}
	SetDirty(false);
}

CD64Image::~CD64Image(void)
{
	if (image != NULL)
		delete image;
	if (bam != NULL)
		delete bam;
}

bool CD64Image::Load(wxString &fileName)
{
	if (image != NULL)
		delete image;

	wxFFile f(fileName, wxT("rb"));
	if (!f.IsOpened())
		return false;
	f.Seek(0, wxFromEnd);
	long size = f.Tell();
	image = new byte[size];
	f.Seek(0, wxFromStart);
	f.Read(image, size);
	f.Close();
	if (size != D64_IMAGE_LENGTH)
		return false;				// not the correct size

	imageLength = size;
	imagePath = fileName;

	InitImage();

	SetDirty(false);

	return true;
}


void CD64Image::InitImage()
{
	if (bam != NULL)
		delete bam;
	bam = GetSector(18, 0);
	lastTrack = 35;
}


void CD64Image::InitBAM(int track, int sector)
{
	wxUnusedVar(track);
	wxUnusedVar(sector);
	throw "InitBAM: The BAM in D64-Images is fixed";
}


int CD64Image::GetSectorOffset(int trackNumber, int sectorNumber)
{
	int offset = 0;
	int i;
	struct
	{
		int TrackStart, TrackEnd, NumSectors;
	} trackInfo[] = 
	{
		{1, 17, 21},
		{18, 24, 19},
		{25, 30, 18},
		{31, 35, 17}
	};

	if (trackNumber < 1 || trackNumber > 35)
	{
		sprintf(msg, "Illegal Track or Sector (%d, %d)", trackNumber, sectorNumber);
		throw msg;
	}

	for (i = 0; i < 4; i++)
	{
		if (trackInfo[i].TrackEnd < trackNumber)
		{
			offset += (trackInfo[i].TrackEnd - trackInfo[i].TrackStart + 1) * trackInfo[i].NumSectors * 256;
		}
		else
		{
			break;
		}
	}
	if (sectorNumber < 0 || sectorNumber > trackInfo[i].NumSectors)
	{
		sprintf(msg, "Illegal Track or Sector (%d, %d)", trackNumber, sectorNumber);
        throw msg;
	}

	offset += ((trackNumber - trackInfo[i].TrackStart) * trackInfo[i].NumSectors * 256) + (sectorNumber * 256);
	return offset;
}


void CD64Image::SetDiskName(unsigned char *diskName)
{
	byte *tRawSec;
	int len = strlen((char*)diskName);
	if (len > 16)
		len = 16;

	tRawSec = bam->GetRawSector();

	memcpy(tRawSec + 144, diskName, len);		// TODO: Check length of diskName ?
	memset(tRawSec + 144 + len, 0xa0, 16 - len);

	WriteSector(bam);
}


void CD64Image::SetDiskID(unsigned char *diskId)
{
	byte *tRawSec;
	int len = strlen((char*)diskId);
	if (len > 5)
		len = 5;

	tRawSec = bam->GetRawSector();

	memcpy(tRawSec + 162, diskId, len);		// TODO: Check length of diskId ?
	memset(tRawSec + 162 + len, 0xa0, 5 - len);

	WriteSector(bam);
}


bool CD64Image::AllocateSector(int track, int sector)
{
	int offset;
	byte bitmask;

	offset = (track-1) * 4 + 4;							// offset to correct Track-Info
	if (bam->GetRawSector()[offset] > 0)
	{
		bam->GetRawSector()[offset] -= 1;				// reduce free Sectors
	}
	offset++;											// Move to Bitmask
	offset += (sector >> 3);							// move to the correct byte (sector div 8)
	bitmask = (byte)(1 << (sector % 8));				// generate Bitmask for Sector
	if ((bam->GetRawSector()[offset] & bitmask) == 0)	// was already set to 'used' ?
	{
		return false;
	}
	bitmask ^= 255;										// invert bitmask (0 means "Sector is used")
	bam->GetRawSector()[offset] &= bitmask;				// clear bit in BAM
	WriteSector(bam);									// Write back to Image
	SetDirty(true);
	return true;
}


bool CD64Image::FreeSector(int track, int sector)
{
	int offset;
	byte bitmask;

	offset = (track - 1) * 4 + 4;						// offset to correct Track-Info
	bam->GetRawSector()[offset] += 1;					// increase free Sectors
	offset++;											// Move to Bitmask
	offset += (sector >> 3);							// move to the correct byte (sector div 8)
	bitmask = (byte)(1 << (sector % 8));				// generate Bitmask for Sector
	if ((bam->GetRawSector()[offset] & bitmask) == 1)	// Sector already free ?
	{
		return false;
	}
	bam->GetRawSector()[offset] |= bitmask;				// clear bit in BAM (1 means "Sector is free")
	WriteSector(bam);									// Write back to Image
	SetDirty(true);
	return true;
}


bool CD64Image::GetNextFreeSector(int startTrack, int startSector, int *foundTrack, int *foundSector)
{
	int track, sector;
	bool found = false;
	bool wrapped = false;
	track = startTrack;

	sector = startSector;
	while (!found)
	{
		if (!IsSectorFree(track, sector))
		{
			if (sector == startSector && track == startTrack)
			{
				sector++;                           // Skip StartSector
				if (wrapped)
				{
					break;							// already wrapped, exit (no free sector found)
				}
			}
			else
			{
				sector++;
			}

			if (sector > GetSectorCount(track, imageType))
			{
				track++;
				sector = 0;
				if (track > lastTrack)
				{
					track = 1;						// Start from the beginning
					wrapped = true;
				}
			}
		}
		else
		{
			found = true;
		}
	}
	*foundTrack = track;
	*foundSector = sector;
	return found;
}


bool CD64Image::IsSectorFree(int track, int sector)
{
	int offset;
	byte bitmask;

	offset = (track-1) * 4 + 4;                 // offset to correct Track-Info
	offset++;									// Move to Bitmask
	offset += (sector >> 3);                    // move to the correct byte (sector div 8)
	bitmask = (byte)(1 << (sector % 8));        // generate Bitmask for Sector
	return (bam->GetRawSector()[offset] & bitmask) == bitmask;
}


bool CD64Image::GetNextDirectorySector(int track, int sector, int *foundTrack, int *foundSector)
{
	if ((sector + 1) > CCbmImageBase::GetSectorCount(35, D64))
	{
		return false;
	}
	*foundTrack = track;
	*foundSector = sector + 1;
	return true;
}


CCbmSector* CD64Image::GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector)
{
	const byte *tRawSec;


	CCbmSector *sectorBuffer = GetSector(bam->GetTrack(), bam->GetSector());		// Read BAM
	tRawSec = sectorBuffer->GetRawSector();

	if( diskName != NULL )
	{
		memcpy(diskName, tRawSec + 144, 16);
	}
	if( diskId != NULL )
	{
		memcpy(diskId, tRawSec + 162, 5);
	}

	*dirTrack = 18;			// sectorBuffer.RawSector[0];		isn't always 18,1 in BAM !
	*dirSector = 1;			// sectorBuffer.RawSector[1];

	return sectorBuffer;
}


int CD64Image::AppendTrack()
{
	throw "AppendTrack is not valid for D64-Images";
}


int CD64Image::GetBlocksFree()
{
	int blocksFree = 0;

	for (int offset = 4; offset < 144; offset += 4)
	{
		if (offset != 72)								// don't count Track 18 !
			blocksFree += bam->GetRawSector()[offset];
	}
	return blocksFree;
}


bool CD64Image::CanIncreaseSize()
{
	return false;
}


int CD64Image::GetImageLength()
{
	return imageLength;
}


int CD64Image::GetNumTracks()
{
	return lastTrack;
}

