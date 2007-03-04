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
