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


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "renamedialog.h"
#endif


#include "wx/dialog.h"
#include "wx/textctrl.h"


#define ID_RENAMEDLG	10009
#define ID_TEXTBOX		10001
#define RENAMEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX



class CRenameDialog :
	public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CRenameDialog )
    DECLARE_EVENT_TABLE()

public:
	CRenameDialog();
	CRenameDialog(wxWindow* parent, const wxString& value);

    /// Creation
    bool Create( wxWindow* parent, const wxString& value = _T(""), wxWindowID id = ID_RENAMEDLG, const wxString& caption = _T("Rename File"),
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = RENAMEDLG_STYLE);

	/// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void OnOK(wxCommandEvent& event);

	wxString GetText();

private:
	wxTextCtrl *m_TextBox;
	wxString m_value;

	wxString m_ReturnValue;
};


