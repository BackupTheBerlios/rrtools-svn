#pragma once
#include "imagebase.h"

#include <wx/wx.h>
#include <wx/string.h>

class CDFIImage :
	public CCbmImageBase
{
public:
	CDFIImage(void);
	~CDFIImage(void);

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
