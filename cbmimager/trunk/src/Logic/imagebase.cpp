#include "imagebase.h"

#include <string.h>
#include <stdio.h>
#include "d64image.h"
#include "dfiimage.h"


CCbmImageBase::CCbmImageBase(void)
{
	image = NULL;
	bam = NULL;
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
    int offset = GetSectorOffset(sector->GetTrack(), sector->GetSector());		// Get offset of Sector
	memcpy(image + offset, sector->GetRawSector(), 256);						// Write data to Image
}


CbmImageType CCbmImageBase::GetImageType()
{
	return imageType;
}


byte* CCbmImageBase::GetRawImage()
{
	return image;
}


CCbmSector *CCbmImageBase::GetBam()
{
	return bam;
}


wxString CCbmImageBase::GetImagePath()
{
	return imagePath;
}