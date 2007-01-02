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

#include "dfiimage.h"
#include <string.h>
#include <memory.h>

#include "wx/ffile.h"


CDFIImage::CDFIImage(void) : CCbmImageBase()
{
	unsigned char buffer[25];

	imageType = DFI;
    image = new byte[256 * 256];
	memset(image, 0, 256 * 256);
	imageLength = 256 * 256;				// Set current Image length
    image[0x100] = 0x01;
    image[0x101] = 0x02;                    // First Directory Sector
    image[0x102] = 0x4d;                    // Format-Char 'M'
	byte* magic = CCbmImageBase::ASCII2PET("DREAMLOAD FILE ARCHIVE", 22, buffer);
    for (int i = 0; i < 22; i++)
        image[i + 1] = (char)magic[i];      // write DFI Magic
    image[0x1a] = 1;                        // Version 1.0
    image[0x1c] = 1;                        // 1 Track in Image
    lastTrack = 1;                          // empty DFI-Image has initially 1 Track
    for (int i = 0x60; i < 0x100; i++)
        image[i] = 0x20;                    // Image Comment
    image[0x20] = 0x01;
    image[0x21] = 0x01;                     // Root Dir
    image[0x22] = 0x01;
    image[0x23] = 0x10;                     // Start of BAM at $1000
	bamStart = 0x1000;						// Set Start of BAM

	for (int i = 0; i < 256; i++)           // Free Sectors in BAM
        FreeSector(1, i);

	InitImage();

    SetDiskName(CCbmImageBase::ASCII2PET("NEW DISK        ", 16, buffer));
    SetDiskID(CCbmImageBase::ASCII2PET("UT 2A", 5, buffer));
}

CDFIImage::~CDFIImage(void)
{
	if (image != NULL)
		delete image;
	if (bam != NULL)
		delete bam;
}


bool CDFIImage::Load(wxString &fileName)
{
	if (image != NULL)
		delete image;

	wxFFile f(fileName, wxT("rb"));
	if (!f.IsOpened())
		return false;
	f.Seek(0, wxFromEnd);
	long size = f.Tell();
	long imageSize = size + (size % 65536);		// Make Size a multiple of 65536 (even Track length)
	image = new byte[imageSize];				// Normally, the length of an DFI-Image is a multiple of 65536
	f.Seek(0, wxFromStart);						// in case it is not, the length is fixed here
	f.Read(image, size);
	f.Close();

	imageLength = imageSize;
	InitImage();

    if (bam->GetRawSector()[2] != 0x4d)			// Check Disk ID 'M'
        return false;
    lastTrack = image[0x1c];

	imagePath = fileName;

	return true;
}


void CDFIImage::InitImage()
{
	if (bam != NULL)
		delete bam;
    CCbmSector *sec = GetSector(1, 0);		// Read DFI-Header
    bam = GetSector(sec->GetRawSector()[0x20], sec->GetRawSector()[0x21]);		// ROOT Sector
    bamStart = GetSectorOffset(sec->GetRawSector()[0x22], sec->GetRawSector()[0x23]);

    AllocateSector(1, 0);                   // Allocate DFI Header
    AllocateSector(1, 1);                   // Allocate Root Sector
    AllocateSector(1, 2);                   // Allocate first Directory Block
	for (int i = 0; i < 32; i++)
		AllocateSector(sec->GetRawSector()[0x22], sec->GetRawSector()[0x23] + i);	// Allocate BAM (32 Sectors)

	delete sec;
}


void CDFIImage::InitBAM(int track, int sector)
{
	if (bam != NULL)
		delete bam;
	bam = NULL;
	bam = GetSector(track, sector);			// Set New Directory Header, but don't change bamStart !
}


int CDFIImage::GetSectorOffset(int trackNumber, int sectorNumber)
{
    if (trackNumber == 0)
        return sectorNumber << 8;
    return ((trackNumber - 1) << 16) + (sectorNumber << 8);
}


void CDFIImage::SetDiskName(unsigned char *diskName)
{
	byte *tRawSec;
	int len = strlen((char*)diskName);
	if (len > 16)
		len = 16;

	CCbmSector *sec = GetSector(image[32], image[33]);
	tRawSec = sec->GetRawSector();

	memcpy(tRawSec + 144, diskName, 16);		// TODO: Check length of diskName ?
	memset(tRawSec + 144 + len, 0xa0, 16 - len);

	WriteSector(sec);
	delete sec;
}


void CDFIImage::SetDiskID(unsigned char *diskId)
{
	byte *tRawSec;
	int len = strlen((char*)diskId);
	if (len > 5)
		len = 5;

	CCbmSector *sec = GetSector(image[32] - 1, image[33]);
	tRawSec = sec->GetRawSector();

	memcpy(tRawSec + 162, diskId, len);		// TODO: Check length of diskId ?
	memset(tRawSec + 162 + len, 0xa0, 5 - len);

	WriteSector(sec);
	delete sec;
}


bool CDFIImage::FreeSector(int track, int sector)
{
    int offset;
    byte bitmask;

	offset = (track - 1) << 5;                  // Track mul 32
    offset += (sector >> 3);                    // sector div 8
    bitmask = (byte)(1 << (sector % 8));        // generate Bitmask for Sector
    if ((image[bamStart + offset] & bitmask) == 0)// was already free ?
        return false;
    bitmask ^= 255;
    image[bamStart + offset] &= bitmask;
	return true;
}


bool CDFIImage::AllocateSector(int track, int sector)
{
    int offset;
    byte bitmask;

	offset = (track - 1) << 5;                  // Track mul 32
    offset += (sector >> 3);                    // sector div 8
    bitmask = (byte)(1 << (sector % 8));        // generate Bitmask for Sector
    if ((image[bamStart + offset] & bitmask) == bitmask)// was already used ?
        return false;
    image[bamStart + offset] |= bitmask;
	return true;
}


bool CDFIImage::GetNextFreeSector(int startTrack, int startSector, int *foundTrack, int *foundSector)
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
                    if (lastTrack < 255)
                    {   // Grow Image by 1 Track
						*foundTrack = AppendTrack();
						*foundSector = 0;
                        return true;
                    }
                    else
                        break;                                  // DFI is full
                }
			}
			else
	            sector++;

			if (sector > 255)
			{
				track++;
				sector = 0;
				if (track > lastTrack)
				{
					track = 1;
					wrapped = true;
				}
			}
		}
		else
			found = true;
    }
	*foundTrack = track;
	*foundSector = sector;
    return found;
}


bool CDFIImage::IsSectorFree(int track, int sector)
{
    int offset;
    byte bitmask;

	offset = (track - 1) << 5;                  // Track mul 32
    offset += (sector >> 3);                    // sector div 8
    bitmask = (byte)(1 << (sector % 8));        // generate Bitmask for Sector
    return (image[bamStart + offset] & bitmask) == 0;
}


bool CDFIImage::GetNextDirectorySector(int track, int sector, int *foundTrack, int *foundSector)
{
	return GetNextFreeSector(track, sector, foundTrack, foundSector);
}


CCbmSector* CDFIImage::GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector)
{
	const byte *tRawSec;


	CCbmSector *sectorBuffer = GetSector(bam->GetTrack(), bam->GetSector());
	tRawSec = sectorBuffer->GetRawSector();

	if( diskName!=NULL )
	{
		memcpy(diskName, tRawSec + 144, 16);
	}
	if( diskId!=NULL )
	{
		memcpy(diskId, tRawSec + 162, 5);
	}

	*dirTrack = sectorBuffer->GetRawSector()[0];
	*dirSector = sectorBuffer->GetRawSector()[1];

	return sectorBuffer;
}


int CDFIImage::AppendTrack()
{
    if (image[0x1c] < 255)
        image[0x1c]++;
    else
        return -1;
	lastTrack++;
	byte *newImage = new byte[256 * 256 * image[0x1c]];
	memset(newImage, 0, 256 * 256 * image[0x1c]);
	memcpy(newImage, image, 256 * 256 * (image[0x1c] - 1));
	delete image;
	image = newImage;
	imageLength = 256 * 256 * image[0x1c];
    for (int i = 0; i < 255; i++)
        FreeSector(image[0x1c], i);				// Free the Track in BAM
    return image[0x1c];
}


int CDFIImage::GetBlocksFree()
{
	int blocksFree = 0;

    int tracks = image[0x1c];
    for (int i = 1; i <= tracks; i++)
    {
        for (int t = 0; t < 256; t++)
        {
            if (IsSectorFree(i, t))
                blocksFree++;
        }
    }
	return blocksFree;
}


bool CDFIImage::CanIncreaseSize()
{
	return true;
}


int CDFIImage::GetImageLength()
{
	return imageLength;
}


int CDFIImage::GetNumTracks()
{
	return lastTrack;
}


