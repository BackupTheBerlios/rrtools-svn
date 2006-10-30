#pragma once
#include "imagebase.h"


#define D64_IMAGE_LENGTH		174848				// Length of a standard D64-Image


class CD64Image :
	public CCbmImageBase
{
public:
	CD64Image(void);
	~CD64Image(void);

	bool Load(wxString &fileName);
	void InitImage();
	void InitBAM(int track, int sector);
	int GetSectorOffset(int trackNumber, int sectorNumber);
	void SetDiskName(unsigned char* diskName);
	void SetDiskID(unsigned char* diskId);
	bool AllocateSector(int track, int sector);
	bool FreeSector(int track, int sector);
	bool GetNextFreeSector(int startTrack, int startSector, int *foundTrack, int *foundSector);
	bool IsSectorFree(int track, int sector);
	bool GetNextDirectorySector(int track, int sector, int *foundTrack, int *foundSector);
	CCbmSector *GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector);
	int AppendTrack();
	int GetBlocksFree();
	bool CanIncreaseSize();
	int GetImageLength();
	int GetNumTracks();

};
