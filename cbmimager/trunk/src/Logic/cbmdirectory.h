#pragma once

#include "cbmsector.h"
#include "cbmdirectoryentry.h"
#include "imagebase.h"

#include "wx/wx.h"

WX_DEFINE_ARRAY(CCbmDirectoryEntry*, DirEntryArray);


/// <summary>
/// This class contains Information about the Directory of an D64-Image
/// </summary>
class CCbmDirectory
{
public:
	/// <summary>
	/// Creates new Directory-Information from a D64-Image
	/// </summary>
	/// <param name="image">The D64-Image</param>
	CCbmDirectory(void);
	CCbmDirectory(CCbmImageBase *image);
	CCbmDirectory(CCbmImageBase *image, int bamTrack, int bamSector);

	~CCbmDirectory(void);


	void ReadFiles(CCbmImageBase *image);

	/// <summary>
	/// Creates a new Directory Entry with the specified Filename in an existing D64-Image
	/// </summary>
	/// <param name="image">D64-Image to create the Entry in</param>
	/// <param name="fileName">Filename of the new Entry (max 16 Chars)</param>
	/// <returns>The created Entry</returns>
	CCbmDirectoryEntry *CreateNewEntry(CCbmImageBase *image, const char *fileName);

	bool ShiftEntries(CCbmImageBase *image, int startIndex, bool shiftRight);

	bool MoveEntry(CCbmImageBase *image, int fromIndex, int toIndex);

	bool CreateSubDirectory(CCbmImageBase *image, const char *name);
	bool SearchFile(CCbmImageBase *image, const char *fileName, bool partial = true);

	// returns the number of files in the given directory
	int GetFileCount(CCbmImageBase *image, CCbmDirectoryEntry *dirEntry);

	/// <summary>
	/// Gets a specific Directory-Entry
	/// </summary>
	/// <param name="index">Index of the Entry</param>
	/// <returns></returns>
	CCbmDirectoryEntry *GetEntry(int index);

	// Removes the Entry with the given entryIndex from the List of DirectoryEntries
	void RemoveEntry(int entryIndex);

	void RecreateDirectory(CCbmImageBase *image);

	int GetEntryCount();

	unsigned char *GetDiskName();

	unsigned char *GetDiskID();


private:

	unsigned char diskName[17];
	unsigned char diskID[6];
	DirEntryArray dirEntries;		// File-Entries
};
