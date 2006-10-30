#pragma once
#include "imagebase.h"

class CD16Image :
	public CCbmImageBase
{
public:
	CD16Image(void);
	~CD16Image(void);


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
	bool GetNextDirectorySector(int track, int sector, int *outTrack, int *outSector);
	CCbmSector *GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector);
	int AppendTrack();
	int GetBlocksFree();
	bool CanIncreaseSize();
	int GetImageLength();
	int GetNumTracks();

};
