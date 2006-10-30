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
