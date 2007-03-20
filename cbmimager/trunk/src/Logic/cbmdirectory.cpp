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


#include "cbmdirectory.h"


/// <summary>
/// This class contains Information about the Directory of an D64-Image
/// </summary>


CCbmDirectory::CCbmDirectory(void)
{
	// clear the complete arrays
	memset(diskName, 0, 17);
	memset(diskID, 0, 6);
}

CCbmDirectory::~CCbmDirectory(void)
{
	int count;
	int i;
	CCbmDirectoryEntry *entry;


	count = (int)dirEntries.Count();
	for (i = 0; i < count; i++)
	{
		entry = dirEntries[0];
		delete entry;
		dirEntries.RemoveAt(0);
	}
}

/// <summary>
/// Creates new Directory-Information from a D64-Image
/// </summary>
/// <param name="image">The D64-Image</param>
CCbmDirectory::CCbmDirectory(CCbmImageBase *image)
{
	// clear the complete arrays
	memset(diskName, 0, 17);
	memset(diskID, 0, 6);

	ReadFiles(image);
}


CCbmDirectory::CCbmDirectory(CCbmImageBase *image, int bamTrack, int bamSector)
{
	// clear the complete arrays
	memset(diskName, 0, 17);
	memset(diskID, 0, 6);

	image->InitBAM(bamTrack, bamSector);
	ReadFiles(image);
}


void CCbmDirectory::ReadFiles(CCbmImageBase *image)
{
	CCbmSector *sectorBuffer = NULL;
	CCbmDirectoryEntry *de = NULL;
	int entryIndex = 0;
	int nextTrack = 0;
	int nextSector = 0;
	int entryOffset = 2;

	sectorBuffer = image->GetHeaderInfo(diskName, diskID, &nextTrack, &nextSector);
	delete sectorBuffer;

	sectorBuffer = image->GetSector(nextTrack, nextSector);
	while (true)
	{
		if (
			sectorBuffer->GetRawSector()[entryOffset] == 255 ||			// Invalid FileType, possible end of Directory
			(sectorBuffer->GetRawSector()[entryOffset + 1] == 0 && 
			sectorBuffer->GetRawSector()[entryOffset + 2] == 0)			// invalid Track/Sector
		   )
		{
			break;
		}
		try
		{
			de = new CCbmDirectoryEntry(image, sectorBuffer, entryOffset);
			de->SetEntryIndex(entryIndex);
		}
		catch( char *text)
		{
			if (de != NULL)
				delete de;
			de = NULL;
			throw text;
		}
		dirEntries.Add(de);

		entryOffset += 32;					// Length of an Directory-Entry
		if (entryOffset > 255)				// Read next Directory-Sector
		{
			entryOffset = 2;
			nextTrack = sectorBuffer->GetRawSector()[0];
			nextSector = sectorBuffer->GetRawSector()[1];
			if (nextTrack == 0)				// end of Directory
			{
				break;
			}
			try
			{
				delete sectorBuffer;
				sectorBuffer = NULL;
				sectorBuffer = image->GetSector(nextTrack, nextSector);
			}
			catch (char* text)
			{
				if (sectorBuffer != NULL)
					delete sectorBuffer;
				sectorBuffer = NULL;
				throw text;
			}
		}
		entryIndex++;
	}
	if (sectorBuffer != NULL)
	{
		delete sectorBuffer;
	}
}


/// <summary>
/// Creates a new Directory Entry with the specified Filename in an existing D64-Image
/// </summary>
/// <param name="image">D64-Image to create the Entry in</param>
/// <param name="fileName">Filename of the new Entry (max 16 Chars)</param>
/// <returns>The created Entry</returns>
CCbmDirectoryEntry *CCbmDirectory::CreateNewEntry(CCbmImageBase *image, const char *fileName)
{
	unsigned char buffer[17];

	int track = 0, sector = 1;
	CCbmSector *sectorBuffer;
	CCbmDirectoryEntry *entry = new CCbmDirectoryEntry();
	CCbmSector *bam = image->GetBam();					                // Read BAM
	// TODO: Use GetHeaderInfo() instead of GetBam() ?
	//if (!image->GetNextFreeSector(1, 0, &track, &sector))				
	//    throw "Disk is full !";

	entry->SetFileStartTrack(track);
	entry->SetFileStartSector(sector);
	entry->SetFileName(CCbmImageBase::ASCII2PET(fileName, 16, buffer));

	// Now write the Entry back to the Image
	int nextTrack = 0;
	int nextSector = 0;
	int entryOffset = 2;
	nextTrack = bam->GetRawSector()[0];
	nextSector = bam->GetRawSector()[1];
	sectorBuffer = image->GetSector(nextTrack, nextSector);
	while (true)
	{
		if (
			sectorBuffer->GetRawSector()[entryOffset + 1] == 0 &&
			sectorBuffer->GetRawSector()[entryOffset + 2] == 0   // Free Entry ? (Track and Sector are zero)
		   )
		{
			break;
		}
		entryOffset += 32;					            // Length of an Directory-Entry
		if (entryOffset > 255)				            // Read next Directory-Sector
		{
			entryOffset = 2;                            // Reset to first Directory-Entry of the Sector
			if (sectorBuffer->GetRawSector()[0] == 0)	// Last Directory Track ?
			{
				if (!image->GetNextDirectorySector(sectorBuffer->GetTrack(), sectorBuffer->GetSector(), &track, &sector))
				{
					throw "The Directory is full !";
				}
				sectorBuffer->SetNextTrack(track);
				sectorBuffer->SetNextSector(sector);
				image->WriteSector(sectorBuffer);       // Write changed Sector back to disk
				delete sectorBuffer;
				sectorBuffer = CCbmSector::Create(track, sector);
				image->AllocateSector(track, sector);
				sectorBuffer->SetNextTrack(0);
				sectorBuffer->SetNextSector(255);		// mark as last Sector of Directory
				image->WriteSector(sectorBuffer);
				entryOffset = 2;
				break;
			}
			nextTrack = sectorBuffer->GetRawSector()[0];
			nextSector = sectorBuffer->GetRawSector()[1];
			delete sectorBuffer;
			sectorBuffer = image->GetSector(nextTrack, nextSector);
		}
	}
	sectorBuffer->GetRawSector()[entryOffset] = (byte)130;						// File Type = PRG (properly Closed)
	sectorBuffer->GetRawSector()[entryOffset + 1] = (byte)entry->GetFileStartTrack();
	sectorBuffer->GetRawSector()[entryOffset + 2] = (byte)entry->GetFileStartSector();  // Start of File
	unsigned char* fname = entry->GetFileName();
	memcpy(sectorBuffer->GetRawSector() + entryOffset + 3, fname, 16);
	image->WriteSector(sectorBuffer);

	delete entry;
	CCbmDirectoryEntry *newEntry = new CCbmDirectoryEntry(image, sectorBuffer, entryOffset);
	delete sectorBuffer;
	return newEntry;
}


bool CCbmDirectory::ShiftEntries(CCbmImageBase *image, int startIndex, bool shiftRight)
{
	if (dirEntries.Count() == 0)
	{
		return true;					// No need to shift
	}
	if (startIndex < 0 || startIndex > (int)dirEntries.Count())
	{
		return false;	// throw "Invalid Shift-Index";
	}

	if (shiftRight)
	{
		CCbmDirectoryEntry *prevEntry = CreateNewEntry(image, "----------------");
		prevEntry->SetBlocksUsed(0);
		prevEntry->SetFileType(CBM_DEL + CBM_CLOSED);
		prevEntry->SetFileStartTrack(0);
		prevEntry->SetFileStartSector(255);
		if (startIndex == (int)dirEntries.Count())
		{
			dirEntries.Add(prevEntry);
		}
		else
		{
			dirEntries.Insert(prevEntry, startIndex);
		}
	}
	else
	{
		delete dirEntries[startIndex - 1];
		dirEntries.RemoveAt(startIndex - 1);
	}

	RecreateDirectory(image);

	return true;
}


bool CCbmDirectory::MoveEntry(CCbmImageBase *image, int fromIndex, int toIndex)
{
	int i;
	CCbmDirectoryEntry *entry = dirEntries[fromIndex];		// Save entry at source position

	if (fromIndex == toIndex)
	{
		return true;
	}
	if (fromIndex > toIndex)								// move up ?
	{
		for (i = fromIndex - 1; i >= toIndex; i--)
		{
			dirEntries[i + 1] = dirEntries[i];
		}
	}
	else													// move down
	{
		for (i = fromIndex + 1; i <= toIndex; i++)
		{
			dirEntries[i - 1] = dirEntries[i];
		}
	}
	dirEntries[toIndex] = entry;

	RecreateDirectory(image);

	return true;
}


bool CCbmDirectory::CreateSubDirectory(CCbmImageBase *image, const char *name)
{
	int track, sector;
	CCbmDirectoryEntry *entry = CreateNewEntry(image, name);
	entry->SetFileType(CBM_DIR + CBM_CLOSED);
	if (image->GetNextFreeSector(1, 0, &track, &sector))		// Search place for Directory Header
	{
		image->AllocateSector(track, sector);
		entry->SetFileStartTrack(track);
		entry->SetFileStartSector(sector);
		entry->Write(image);
		CCbmSector *sec = image->GetSector(track, sector);
		if (image->GetNextFreeSector(track, sector, &track, &sector))	// Search place for first Directory Block
		{
			image->AllocateSector(track, sector);
			sec->GetRawSector()[0] = track;
			sec->GetRawSector()[1] = sector;
			sec->GetRawSector()[2] = 'M';						// Format-Character
			CCbmImageBase::ASCII2PET(name, 16, &sec->GetRawSector()[0x90]);
			CCbmImageBase::ASCII2PET("MOOH!", 5, &sec->GetRawSector()[0xa2]);
			sec->GetRawSector()[0xa7] = 0xa0;					// Shifted Space
			sec->GetRawSector()[0xa8] = 0xa0;					// Shifted Space
			sec->GetRawSector()[0xa9] = 0xa0;					// Shifted Space
			sec->GetRawSector()[0xaa] = 0xa0;					// Shifted Space
			image->WriteSector(sec);
			delete sec;
			sec = image->GetSector(track, sector);
			sec->GetRawSector()[0] = 0;
			sec->GetRawSector()[1] = 0;							// Mark as last Sector in Directory
			sec->GetRawSector()[2] = 0;
			image->WriteSector(sec);
			delete sec;
			return true;
		}
		delete sec;
	}
	return false;
}


bool CCbmDirectory::SearchFile(CCbmImageBase *image, const char *fileName, bool partial, bool searchSubDirs)
{
	int i;
	bool result = false;
	CCbmDirectory *subDir = NULL;


	try
	{
		for (i = 0; i < (int)dirEntries.Count(); i++)
		{
			CCbmDirectoryEntry *entry = dirEntries[i];
			if (entry->GetFileType() == CBM_DIR && image->GetImageType() == DFI)
			{
				if (searchSubDirs)
				{
					subDir = new CCbmDirectory(image, entry->GetFileStartTrack(), entry->GetFileStartSector());
					result = subDir->SearchFile(image, fileName, partial);
					delete subDir;
					subDir = NULL;
				}
			}
			else
			{
				wxString name;
				name = CCbmImageBase::PET2String(entry->GetFileName(), 0, 16);
				if (partial)
				{
					if (name.Contains(wxString::FromAscii(fileName)) == 1)
						result = true;
				}
				else
				{
					if (name.Cmp(wxString::FromAscii(fileName)) == 0)
						result = true;
				}
			}
			if (result)
				break;
		}
	}
	catch (...) {} 		// Skip exceptions

	if (subDir != NULL)
		delete subDir;

	return result;
}


// returns the number of files in the given directory
int CCbmDirectory::GetFileCount(CCbmImageBase *image, CCbmDirectoryEntry *dirEntry)
{
	int track, sector;
	int numFiles;

	if (dirEntry->GetFileType() != CBM_DIR)
	{
		return -1;								// only valid for directorys
	}

	track = image->GetBam()->GetTrack();
	sector = image->GetBam()->GetSector();		// save position of old bam
	CCbmDirectory *dir = new CCbmDirectory(image, dirEntry->GetFileStartTrack(), dirEntry->GetFileStartSector());
	numFiles = dir->GetEntryCount();
	image->InitBAM(track, sector);				// Restore old BAM
	delete dir;
	return numFiles;
}


/// <summary>
/// Gets a specific Directory-Entry
/// </summary>
/// <param name="index">Index of the Entry</param>
/// <returns></returns>
CCbmDirectoryEntry *CCbmDirectory::GetEntry(int index)
{
	if (index < 0 || index > (int)dirEntries.Count())
	{
		throw "Index out of range";
	}
	return (CCbmDirectoryEntry*)dirEntries[index];
}


// Removes the Entry with the given entryIndex from the List of DirectoryEntries
void CCbmDirectory::RemoveEntry(int entryIndex)
{
	for (int i = 0; i < (int)dirEntries.Count(); i++)
	{
		if (((CCbmDirectoryEntry*)dirEntries[i])->GetEntryIndex() == entryIndex)
		{
			dirEntries.RemoveAt(i);
			return;
		}
	}
}


void CCbmDirectory::RecreateDirectory(CCbmImageBase *image)
{
	int track, sector, entryOffset;
	CCbmSector *sec;

	CCbmDirectoryEntry *fakeEntry = new CCbmDirectoryEntry();
	fakeEntry->SetFileStartTrack(0);
	fakeEntry->SetFileStartSector(0);
	fakeEntry->SetFileType(0);
	dirEntries.Add(fakeEntry);									// Add a fake Empty Entry at the end of the Directory

	sec = image->GetHeaderInfo(NULL, NULL, &track, &sector);// Get Directory Start
	delete sec;
	entryOffset = 2;
	for (int i = 0; i < (int)dirEntries.Count(); i++)
	{
		CCbmDirectoryEntry *entry = dirEntries[i];
		entry->SetImageOffset(image, track, sector, entryOffset);
		entry->Write(image);
		entryOffset += 32;
		if (entryOffset > 255)
		{
			sec = image->GetSector(track, sector);				// Read current directory Sector
			if (!image->GetNextDirectorySector(track, sector, &track, &sector))
				throw "Directory is full";
			entryOffset = 2;
			sec->SetNextTrack(track);
			sec->SetNextSector(sector);							// Link to the next sector
			image->WriteSector(sec);
			delete sec;
		}
	}

	dirEntries.RemoveAt(dirEntries.Count() - 1);				// Remove fake entry
	delete fakeEntry;
}


int CCbmDirectory::GetEntryCount()
{
	return dirEntries.Count();
}

unsigned char *CCbmDirectory::GetDiskName()
{
	return diskName;
}

unsigned char *CCbmDirectory::GetDiskID()
{
	return diskID;
}


