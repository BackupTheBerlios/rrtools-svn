

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
