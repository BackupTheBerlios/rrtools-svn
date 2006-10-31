#pragma once

#include "cbmsector.h"

#include "wx/wx.h"
#include "wx/string.h"

typedef unsigned char byte;


typedef enum CbmImageType
{
	D64,
	DFI,
	D16,
	NONE
};


class CCbmImageBase
{
public:
	CCbmImageBase(void);
	virtual ~CCbmImageBase(void);

	virtual bool Load(wxString &fileName) = 0;
	virtual void InitImage() = 0;
	virtual void InitBAM(int track, int sector) = 0;
	virtual int GetSectorOffset(int trackNumber, int sectorNumber) = 0;
	virtual void SetDiskName(unsigned char* diskName) = 0;
	virtual void SetDiskID(unsigned char* diskId) = 0;
	virtual bool AllocateSector(int track, int sector) = 0;
	virtual bool FreeSector(int track, int sector) = 0;
	virtual bool GetNextFreeSector(int startTrack, int startSector, int *foundTrack, int *foundSector) = 0;
	virtual bool IsSectorFree(int track, int sector) = 0;
	virtual bool GetNextDirectorySector(int track, int sector, int *outTrack, int *outSector) = 0;
	virtual CCbmSector *GetHeaderInfo(unsigned char *diskName, unsigned char *diskId, int *dirTrack, int *dirSector) = 0;
	virtual int AppendTrack() = 0;
	virtual int GetBlocksFree() = 0;
	virtual bool CanIncreaseSize() = 0;
	virtual int GetImageLength() = 0;
	virtual int GetNumTracks() = 0;

	CCbmSector *GetSector(int track, int sector);
	void WriteSector(CCbmSector *sector);
	CbmImageType GetImageType();
	byte* GetRawImage();
	CCbmSector *GetBam();
	wxString GetImagePath();

	static CCbmImageBase *Create(CbmImageType type);
	static char* PET2ASCII(const unsigned char *text, int startOffset, int length, char* dest);
	static unsigned char* ASCII2PET(const char *text, int length, unsigned char* dest);
	static int GetSectorCount(int trackNumber, CbmImageType imageType);

protected:
	CbmImageType imageType;
	wxString imagePath;					// Path to the Image-File
	byte* image;						// complete Disk-Data
	int imageLength;					// size of the current Image
	CCbmSector *bam;					// BAM of the D64 Image (only used with .D64-Images)
	int bamStart;                       // Offset in Image to the start of the BAM (only used with D16 and DFI)
	int lastTrack;                      // last Track in actual Image

	char msg[600];						// Buffer for internal use (Error messages etc)
};
