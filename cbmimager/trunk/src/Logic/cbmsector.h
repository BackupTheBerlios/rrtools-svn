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

#include <stdlib.h>
#include <memory.h>


typedef unsigned char byte;


// This class contains Information about a complete Sector (256-byte array) of an D64-Image
class CCbmSector
{
public:
	CCbmSector(void)
	{
		trackData = NULL;
	}

	~CCbmSector(void)
	{
		if (trackData != NULL)
			delete trackData;
	}

    CCbmSector(byte* data)
    {
		trackData = new byte[256];
		memcpy(trackData, data, 256);
    }

    /// <summary>
    /// Creates a new empty Sector with specific Track and Sector Information
    /// </summary>
    /// <param name="track">Desired Track</param>
    /// <param name="sector">Desired Sector</param>
    /// <returns>The created Sector</returns>
    static CCbmSector* Create(int track, int sector)
    {
		byte buf[256];
        CCbmSector *sec = new CCbmSector(buf);
		memset(sec->GetRawSector(), 0, 256);             // Set all Bytes to zero
        sec->SetTrack(track);
        sec->SetSector(sector);
        return sec;
    }

    int GetTrack()
    {
        return track;
	}
	void SetTrack(int value)
	{
        track = value;
    }

    int GetSector()
    {
        return sector;
	}
	void SetSector(int value)
	{
        sector = value;
    }

    int GetNextTrack()
    {
        return (int)trackData[0];
	}
	void SetNextTrack(int value)
	{
        trackData[0] = (char)(value & 255);
    }

    int GetNextSector()
    {
        return (int)trackData[1];
	}
	void SetNextSector(int value)
	{
        trackData[1] = (char)(value & 255);
    }

    byte* GetRawSector()
    {
        return trackData;
    }

private:

    byte* trackData;
    int track, sector;
};
