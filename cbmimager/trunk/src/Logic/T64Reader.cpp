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


#include "T64Reader.h"

#include "wx/ffile.h"
#include "wx/filename.h"


CT64Reader::CT64Reader(void)
{
	buffer = NULL;
}

CT64Reader::~CT64Reader(void)
{
	unsigned int i = 0;
	for (i = 0; i < filenames.Count(); i++)
	{
		wxRemoveFile(filenames[i]);
	}
}

// Reads the contents of a T64 Image
// The import is a quick and dirty approach :
// The files from the image were stored as Pxx-Files in the system's temp-folder, then imported by CBMImager.AddFile()
// (see CBMImager::OnMenuextrasImportT64)
int CT64Reader::Read(wxString filename)
{
	int i, numFiles = 0, fileLength;
	wxFileName fileName;
	wxString name;
	struct
	{
		char magic[7];
		char zero1;
		char filename[16];
		char zero2;
		char recordLength;
	} p00Header;


	memset(&p00Header, 0, sizeof(p00Header));
	sprintf(p00Header.magic, "C64File");

	wxFFile f(filename, wxT("rb"));
	if (!f.IsOpened())
		return -1;

	f.Read(&fileHeader, sizeof(_T64Header));
	fileHeader.UserDescr[23] = 0;
	fileHeader.description[31] = 0;
	fileEntries = (_T64FileEntry*)malloc(sizeof(_T64FileEntry) * fileHeader.MaxFiles);
	// Read FileEntries
	for (i = 0; i < fileHeader.MaxFiles; i++)
	{
		f.Read(&fileEntries[i], sizeof(_T64FileEntry));
	}
	for (i = 0; i < fileHeader.MaxFiles; i++)
	{
		if (fileEntries[i].EntryUsed == 1)
		{
			fileLength = fileEntries[i].EndAddr - fileEntries[i].StartAddr;
			f.Seek(fileEntries[i].TapePos, wxFromStart);
			buffer = (byte*)malloc(fileLength);
			f.Read(buffer, fileLength);
			fileName.AssignTempFileName(wxT(""));
			if (fileName.IsOk())
			{
				name.Printf("%s%cT64.P%02d", fileName.GetPath(), fileName.GetPathSeparator(), numFiles);
				wxFFile output(name, wxT("wb"));
				if (output.IsOpened())
				{
					memcpy(p00Header.filename, fileEntries[i].FileName, 16);
					output.Write(&p00Header, sizeof(p00Header));						// Write the P00 Header
					output.Write(&fileEntries[i].StartAddr, sizeof(unsigned short));	// Write File's Startaddress
					output.Write(buffer, fileLength);									// Write File-content
					output.Close();
					numFiles++;
					if (numFiles > 99)
					{
						wxLogMessage(_T("T64-Image contains more than 99 Files, additional files were ignored"));
						return 99;
					}
					filenames.Add(name);
				}
			}
			free(buffer);
		}
	}
	return numFiles;
}


wxString& CT64Reader::GetExtractedFileName(int number) const
{
	return filenames[number];
}
