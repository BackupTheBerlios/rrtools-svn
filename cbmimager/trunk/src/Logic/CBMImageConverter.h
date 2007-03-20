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

#include "../cbmimager_version.h"
#include "imagebase.h"
#include "cbmdirectory.h"
#include "cbmdirectoryentry.h"
#include "dfiimage.h"
#include "d64image.h"


class CCBMImageConverter
{
public:
	CCBMImageConverter(void);
	~CCBMImageConverter(void);

	CCbmImageBase *ConvertImage(CCbmImageBase *sourceImage, CbmImageType outputType);
	void SetValid();

protected:
	bool AddFileEntry(CCbmDirectoryEntry *entry);

	CCbmImageBase *outImage, *sourceImage;
	CCbmDirectory *outDir, *sourceDir;
};
