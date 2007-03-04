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

#include "imagebase.h"

#include <string.h>
#include <stdio.h>
#include "d64image.h"
#include "dfiimage.h"


CCbmImageBase::CCbmImageBase(void)
{
	image = NULL;
	bam = NULL;
	dirty = false;
}

CCbmImageBase::~CCbmImageBase(void)
{
}

CCbmImageBase* CCbmImageBase::Create(CbmImageType type)
{
	switch (type)
	{
		case D64:
			return new CD64Image();
		case DFI:
			return new CDFIImage();
		default:
			return NULL;
	}
}

wxString CCbmImageBase::PET2String(const unsigned char *text, int startOffset, int length)
{
	wxString str;
	const unsigned char *pcCnt, *pcEnd;
	unsigned char bPetscii;
	char cAscii;


	// get pointer to start and end of the PETSCII string
	pcCnt = text + startOffset;
	pcEnd = pcCnt + length;

	// convert all bytes to ascii
	while( pcCnt<pcEnd )
	{
		bPetscii = *(pcCnt++);
		if (bPetscii == 160)				// $A0
			break;
		cAscii = bPetscii;

		str += cAscii;
	}

	return str;
}

char* CCbmImageBase::PET2ASCII(const unsigned char *text, int startOffset, int length, char* dest)
{
	static byte temp[64];		// TODO: prevent buffer overrun
	int i, t;
	for (i = startOffset, t = 0; i < startOffset + length; i++, t++)
	{
		if (text[i] == 160)				// $A0 ?
			break;
		temp[t] = text[i];
	}
	temp[t] = 0;
	strcpy(dest, (char*)temp);
	return dest;
}

unsigned char* CCbmImageBase::ASCII2PET(const char *text, int length, unsigned char* dest)
{
	int iCnt;


	for(iCnt = 0; iCnt < length; ++iCnt)
	{
		if (text[iCnt] >= 97 && text[iCnt] <= 122)
			dest[iCnt] = text[iCnt] - 32;
//		else if (text[i] == 160)
//			temp[i] = ' ';
		else
			dest[iCnt] = text[iCnt];
		if (text[iCnt] == 0)
			break;
	}
	dest[iCnt] = 0;

	return dest;
}


/// <summary>
/// Gets the number of Sectors for a specific Track
/// </summary>
/// <param name="trackNumber">Number of Track (1 - 35)</param>
/// <returns>Number of Sectors in the specified Track</returns>
int CCbmImageBase::GetSectorCount(int trackNumber, CbmImageType imageType)
{
    int i = 0;
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

    switch (imageType)
    {
        case D64:
            for (i = 0; i < 4; i++)
            {
                if (trackInfo[i].TrackStart <= trackNumber && trackInfo[i].TrackEnd >= trackNumber)
                    return trackInfo[i].NumSectors;
            }
            break;
        case D16:
        case DFI:
            return 256;     // Sector-Count for HD- and DFI-Images
    }
    return 0;
}


CCbmSector *CCbmImageBase::GetSector(int track, int sector)
{
    byte sectorBuffer[256];
    int offset = GetSectorOffset(track, sector);
    if (imageLength <= offset)
	{
		sprintf(msg, "Illegal Track or Sector (%d, %d)", track, sector);
        throw msg;
	}

	memcpy(sectorBuffer, image + offset, 256);
    CCbmSector *sec = new CCbmSector(sectorBuffer);
    sec->SetTrack(track);
    sec->SetSector(sector);
    return sec;
}


void CCbmImageBase::WriteSector(CCbmSector *sector)
{
//	if (sector->GetTrack() == 1 && sector->GetSector() == 33)
//		int i = 0;
    int offset = GetSectorOffset(sector->GetTrack(), sector->GetSector());		// Get offset of Sector
	memcpy(image + offset, sector->GetRawSector(), 256);						// Write data to Image
	SetDirty(true);
}


CbmImageType CCbmImageBase::GetImageType()
{
	return imageType;
}

bool CCbmImageBase::IsDirty()
{
	return dirty;
}

void CCbmImageBase::SetDirty(bool dirty)
{
	this->dirty = dirty;
}

/*
byte* CCbmImageBase::GetRawImage()
{
	return image;
}
*/
byte CCbmImageBase::ReadByte(int offset)
{
	return image[offset];
}

void CCbmImageBase::ReadContent(byte *dest, int startOffset, int length)
{
	memcpy(dest, &image[startOffset], length);
}

void CCbmImageBase::WriteByte(byte value, int offset)
{
	image[offset] = value;
	SetDirty(true);
}

void CCbmImageBase::WriteContent(byte *data, int startOffset, int length)
{
	memcpy(&image[startOffset], data, length);
	SetDirty(true);
}


CCbmSector *CCbmImageBase::GetBam()
{
	return bam;
}


wxString CCbmImageBase::GetImagePath()
{
	return imagePath;
}
