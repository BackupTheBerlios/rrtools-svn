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

#include <wx/wx.h>


#ifndef __CBMIMAGER_ID_H__
#define __CBMIMAGER_ID_H__


// menu ids for cbmimager main window
#define CMD_ADD_FILES		1
#define CMD_DELETE_FILES	2
#define CMD_EXTRACT_FILES	3
#define CMD_RENAME_FILE		4
#define CMD_SHIFT_UP		5
#define CMD_SEP_BEFORE		6
#define CMD_SEP_AFTER		7
#define CMD_CREATE_SUBDIR	8
#define CMD_RENAME_DISK		9
#define CMD_CONVERT			10
#define CMD_CONVERT_PRG		11
#define CMD_CONVERT_USR		12
#define CMD_CONVERT_SEQ		13
#define CMD_CONVERT_REL		14
#define CMD_CONVERT_DEL		15
#define CMD_SET_SCRATCH_PROTECTION		16
#define CMD_DEL_SCRATCH_PROTECTION		17
#define CMD_SET_CLOSED_FLAG				18
#define CMD_DEL_CLOSED_FLAG				19
#define CMD_EXPORT_P00					20


// external event
DECLARE_EXPORTED_EVENT_TYPE(EMPTY_PARAMETER_VALUE, wxEVT_ODLISTBOX_DRAG_EVENT, 0)
DECLARE_EXPORTED_EVENT_TYPE(EMPTY_PARAMETER_VALUE, wxEVT_ODLISTBOX_SELECTION_EVENT, 0)

// event table id for the new type
#define EVT_ODLISTBOX_DRAG_EVENT(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
		wxEVT_ODLISTBOX_DRAG_EVENT, id, wxID_ANY, \
		(wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
		(wxObject *) NULL \
	),

#define EVT_ODLISTBOX_SELECTION_EVENT(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
		wxEVT_ODLISTBOX_SELECTION_EVENT, id, wxID_ANY, \
		(wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
		(wxObject *) NULL \
	),


// object identifiers
enum
{
	ID_CBMIMAGER		= wxID_HIGHEST,
	ID_MENUFILENEW,
	ID_MENUFILEOPEN,
	ID_MENUFILESAVE,
	ID_MENUFILESAVEAS,
	ID_MENUFILESEARCH,
	ID_MENUFILEEXIT,
	ID_MENUEXTRAS_EDITFILE,
	ID_MENUEXTRAS_EDITBAM,
	ID_LISTBOXFILES,
	ID_STATUSBAR
};



#endif	// __CBMIMAGER_ID_H__
