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


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "selectimage.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "renamedialog.h"



IMPLEMENT_DYNAMIC_CLASS( CRenameDialog, wxDialog )

BEGIN_EVENT_TABLE( CRenameDialog, wxDialog )
	EVT_BUTTON(wxID_OK, CRenameDialog::OnOK)
END_EVENT_TABLE()




CRenameDialog::CRenameDialog()
{
	Init();
}

CRenameDialog::CRenameDialog(wxWindow* parent, const wxString& value)
{
	Init();
	Create(parent, value);
}

bool CRenameDialog::Create( wxWindow* parent, const wxString& value, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

	m_value = value;

    CreateControls();
    if (GetSizer())
    {
		GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}


void CRenameDialog::Init()
{
}


void CRenameDialog::CreateControls()
{
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemBoxSizer2);

	m_TextBox = new wxTextCtrl(this, ID_TEXTBOX, m_value);
	itemBoxSizer2->Add(m_TextBox, 1, wxEXPAND|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxButton* itemButton5 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton6 = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	itemButton6->SetDefault();

	m_TextBox->SetValue(m_value);
}


void CRenameDialog::OnOK(wxCommandEvent& event)
{
	if (m_TextBox->GetValue().Len() == 0 || m_TextBox->GetValue().Len() > 16)
		return;
	m_ReturnValue = m_TextBox->GetValue();
	event.Skip();
}



wxString CRenameDialog::GetText()
{
	return m_ReturnValue;
}
