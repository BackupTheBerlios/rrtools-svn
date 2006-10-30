#include "d16image.h"

#include <string.h>
#include <memory.h>

#include "wx/wx.h"
#include "wx/ffile.h"


CD16Image::CD16Image(void) : CCbmImageBase()
{
	imageType = D16;
}

CD16Image::~CD16Image(void)
{
	if (image != NULL)
		delete image;
	if (bam != NULL)
		delete bam;
}


bool CD16Image::Load(wxString &fileName)
{
	if (image != NULL)
		delete image;

	wxFFile f(fileName, wxT("rb"));
	if (!f.IsOpened())
		return false;
	f.Seek(0, wxFromEnd);
	long size = f.Tell();
	image = new byte[size];
	f.Seek(0);
	f.Read(image, size);
	f.Close();

	imageLength = size;
	lastTrack = imageLength / 256;
	InitImage();

    if (bam->GetRawSector()[2] != 0x48)     // Check Disk ID 'H'
        return false;

	imagePath = fileName;

	return true;
}


void CD16Image::InitImage()
{
	if (bam != NULL)
		delete bam;
    bam = GetSector(1, 1);					// Bam of an HD Image seems to start at $100
    bamStart = GetSectorOffset(1, 1);
}


void CD16Image::InitBAM(int track, int sector)
{
	if (bam != NULL)
		delete bam;
	bam = NULL;
	bam = GetSector(track, sector);
	bamStart = GetSectorOffset(track, sector);
}


int CD16Image::GetSectorOffset(int trackNumber, int sectorNumber)
{
    if (trackNumber == 0)
        return sectorNumber << 8;
    return ((trackNumber - 1) << 16) + (sectorNumber << 8);
}


void CD16Image::SetDiskName(unsigned char *diskName)
{
	wxUnusedVar(diskName);
}


void CD16Image::SetDiskID(unsigned char *diskId)
{
	wxUnusedVar(diskId);
}


bool CD16Image::AllocateSector(int track, int sector)
{
	wxUnusedVar(track);
	wxUnusedVar(sector);
	return false;
}


bool CD16Image::FreeSector(int track, int sector)
{
	wxUnusedVar(track);
	wxUnusedVar(sector);
	return false;
}


bool CD16Image::GetNextFreeSector(int startTrack, int startSector, int *foundTrack, int *foundSector)
{
	wxUnusedVar(startTrack);
	wxUnusedVar(startSector);
	wxUnusedVar(foundTrack);
	wxUnusedVar(foundSector);
    return false;
}


bool CD16Image::IsSectorFree(int track, int sector)
{
	wxUnusedVar(track);
	wxUnusedVar(sector);
	return false;
}


bool CD16Image::GetNextDirectorySector(int track, int sector, int *foundTrack, int *foundSector)
{
	wxUnusedVar(track);
	wxUnusedVar(sector);
	wxUnusedVar(foundTrack);
	wxUnusedVar(foundSector);
	return false;
}


CCbmSector* CD16Image::GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector)
{
	const byte *tRawSec;


	CCbmSector *sectorBuffer = GetSector(bam->GetTrack(), bam->GetSector());		// Read BAM
	tRawSec = sectorBuffer->GetRawSector();

	if( diskName!=NULL )
	{
		memcpy(diskName, tRawSec+4, 16);
	}
	if( diskId!=NULL )
	{
		memcpy(diskId, tRawSec+22, 5);
	}

	*dirTrack = sectorBuffer->GetRawSector()[0];
	*dirSector = sectorBuffer->GetRawSector()[1];

	return sectorBuffer;
}


int CD16Image::AppendTrack()
{
	throw "AppendTrack is not valid for D16-Images";
}


int CD16Image::GetBlocksFree()
{
	int blocksFree = 0;
	return blocksFree;
}


bool CD16Image::CanIncreaseSize()
{
	return false;
}


int CD16Image::GetImageLength()
{
	return imageLength;
}


int CD16Image::GetNumTracks()
{
	return lastTrack;
}
