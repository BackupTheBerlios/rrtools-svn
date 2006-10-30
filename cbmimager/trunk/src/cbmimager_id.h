
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


// external event
DECLARE_EXPORTED_EVENT_TYPE(, wxEVT_ODLISTBOX_DRAG_EVENT, 0)
DECLARE_EXPORTED_EVENT_TYPE(, wxEVT_ODLISTBOX_SELECTION_EVENT, 0)

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
