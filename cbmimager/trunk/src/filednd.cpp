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

#include "filednd.h"

#include "Logic/imagebase.h"
#include "Logic/d64image.h"
#include "Logic/dfiimage.h"
#include "Logic/cbmsector.h"
#include "Logic/cbmdirectoryentry.h"
#include "Logic/cbmdirectory.h"



DnDFile::DnDFile(CBMImager *pOwner)
{ 
	m_pOwner = pOwner; 
}


bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
    size_t nFiles = filenames.GetCount();
    for ( size_t n = 0; n < nFiles; n++ ) 
	{
		m_pOwner->AddFile(filenames[n]);
    }
    return true;
}


wxDragResult DnDFile::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
	wxUnusedVar(x);
	wxUnusedVar(y);
	if (m_pOwner->GetCurrentImageType() == D16 || m_pOwner->GetCurrentImageType() == NONE || m_pOwner->IsDragSource())
		return wxDragNone;
	return def;
}
