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

#ifndef _DNDFILE_H_INCLUDED
#define _DNDFILE_H_INCLUDED

#include "wx/wx.h"
#include "wx/dnd.h"
#include "odlistbox.h"
#include "cbmimager.h"

class DnDFile : public wxFileDropTarget
{
public:
	DnDFile(CBMImager *pOwner);

    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                             const wxArrayString& filenames);
	
	wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);

private:
    CBMImager *m_pOwner;
};


#endif //_DNDFILE_H_INCLUDED

