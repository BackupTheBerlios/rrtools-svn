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

#include "cbmimager_id.h"

#if WXWIN_COMPATIBILITY_EVENT_TYPES
#error "CBMImager needs new event types"
#endif

// new event type for odlistbox drags and selections
DEFINE_EVENT_TYPE(wxEVT_ODLISTBOX_DRAG_EVENT)
DEFINE_EVENT_TYPE(wxEVT_ODLISTBOX_SELECTION_EVENT)


BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_ODLISTBOX_DRAG_EVENT, wxID_ANY)
	DECLARE_EVENT_TYPE(wxEVT_ODLISTBOX_SELECTION_EVENT, wxID_ANY)
END_DECLARE_EVENT_TYPES()


