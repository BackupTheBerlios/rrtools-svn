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


#include <wx/dialog.h>
#include "Logic/imagebase.h"


#define ID_NEWIMAGEDLG		10009
#define ID_RBD64			10001
#define ID_RBDFI			10002
#define NEWIMAGEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX


class CNewImage :
	public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CNewImage )
    DECLARE_EVENT_TABLE()

public:
	CNewImage(void);
	CNewImage(wxWindow* parent);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = ID_NEWIMAGEDLG, const wxString& caption = _T("Create new Image"),
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = NEWIMAGEDLG_STYLE);

	/// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void OnOK(wxCommandEvent& event);

	CbmImageType GetImageType();

private:
	wxRadioButton *m_rbDFI;
	wxRadioButton *m_rbD64;

	CbmImageType m_imageType;
};
