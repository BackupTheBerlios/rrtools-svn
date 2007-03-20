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

#include "cbmimageconverter.h"

#include "wx/wx.h"
#include "wx/string.h"



CCBMImageConverter::CCBMImageConverter(void)
{
	outImage = NULL;
	outDir = NULL;
}

CCBMImageConverter::~CCBMImageConverter(void)
{
	if (outDir != NULL)
		delete outDir;
	if (outImage != NULL)
		delete outImage;
}


// This function prevents the converted Image from deletion in the destructor
void CCBMImageConverter::SetValid()
{
	outImage = NULL;
}


CCbmImageBase* CCBMImageConverter::ConvertImage(CCbmImageBase *sourceImage, CbmImageType outputType)
{
	int i;

	this->sourceImage = sourceImage;
	switch (outputType)
	{
		case DFI:
			outImage = new CDFIImage();
			break;
		case D64:
			outImage = new CD64Image();
			break;
		default:
			throw "Can only convert to DFI or D64";
			break;
	}
	outDir = new CCbmDirectory(outImage);
	sourceDir = new CCbmDirectory(sourceImage);
	for (i = 0; i < sourceDir->GetEntryCount(); i++)
	{
		AddFileEntry(sourceDir->GetEntry(i));
	}
	outImage->SetDiskName(sourceDir->GetDiskName());
	outImage->SetDiskID(sourceDir->GetDiskID());
	delete sourceDir;
	sourceDir = NULL;
	return outImage;
}


bool CCBMImageConverter::AddFileEntry(CCbmDirectoryEntry *entry)
{
	CCbmDirectoryEntry *newEntry = NULL;
	byte *fileBuffer = NULL;
	byte buffer[256];
	int blockStart;
	int track, sector, newTrack, newSector;
	int dirTrack, dirSector;
	int bufferLength, readBytes;

	try
	{
		newEntry = outDir->CreateNewEntry(outImage, (char*)entry->GetFileName());
	}
	catch (char *text)
	{
		if (newEntry != NULL)
			delete newEntry;
		throw text;
	}
	CCbmSector *sec = sourceImage->GetHeaderInfo(NULL, NULL, &dirTrack, &dirSector);
	delete sec;
	// We won't process DEL Files or Files pointing into the Directory
	if (entry->GetFileType() != CBM_DEL && (entry->GetFileStartTrack() != dirTrack || entry->GetFileStartSector() != dirSector))
	{
		// Maybe we allocated a new Directory Sector in CreateNewEntry(), so check again for free sectors for the file
		if (!outImage->GetNextFreeSector(1, 0, &track, &sector))
		{
			newEntry->DeleteFile(outImage);			// delete incomplete File
			delete newEntry;
			throw "Disk full";
		}
		newEntry->SetFileStartTrack(track);
		newEntry->SetFileStartSector(sector);

		bufferLength = entry->GetFileContent(sourceImage, &fileBuffer);
		blockStart = 0;
		if ((blockStart + 254) > bufferLength)
			readBytes = bufferLength - blockStart;
		else
			readBytes = 254;
		while (readBytes > 0)
		{
			memcpy(&buffer[2], &fileBuffer[blockStart], readBytes);
			newEntry->SetBlocksUsed(newEntry->GetBlocksUsed() + 1);
			if (!outImage->AllocateSector(track, sector))
			{
				newEntry->DeleteFile(outImage);			// delete incomplete File
				delete newEntry;
				throw "Disk full";
			}
			if (readBytes < 254 || (blockStart + readBytes) >= bufferLength)	// End of Input-File ?
			{
				buffer[0] = 0;
				buffer[1] = (byte)(readBytes + 1);		// Mark End of File
			}
			else
			{
				if (!outImage->GetNextFreeSector(track, sector, &newTrack, &newSector))
				{
					entry->DeleteFile(outImage);		// delete incomplete File
					delete newEntry;
					throw "Disk full";
				}
				buffer[0] = (byte)newTrack;
				buffer[1] = (byte)newSector;
			}
			CCbmSector *sec = new CCbmSector(buffer);
			sec->SetTrack(track);
			sec->SetSector(sector);
			outImage->WriteSector(sec);
			delete sec;
			track = buffer[0];
			sector = buffer[1];
			memset(buffer, 0, 256);						// Clear buffer before the next Read-Action
			// Read next block
			blockStart += readBytes;
			if ((blockStart + 254) > bufferLength)
				readBytes = bufferLength - blockStart;
			else
				readBytes = 254;
		}
		free(fileBuffer);
	}
	newEntry->SetFileType(entry->GetFileType());
	newEntry->SetClosedProperly(entry->GetClosedProperly());
	newEntry->SetScratchProtected(entry->GetScratchProtected());
	newEntry->Write(outImage);
	delete newEntry;

	return true;
}

