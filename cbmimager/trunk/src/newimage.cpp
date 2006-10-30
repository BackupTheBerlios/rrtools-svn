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


#include "newimage.h"



IMPLEMENT_DYNAMIC_CLASS( CNewImage, wxDialog )

BEGIN_EVENT_TABLE( CNewImage, wxDialog )
	EVT_BUTTON(wxID_OK, CNewImage::OnOK)
END_EVENT_TABLE()



CNewImage::CNewImage(void)
{
	Init();
}

CNewImage::CNewImage(wxWindow* parent)
{
	Init();
	Create(parent);
}


bool CNewImage::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
		GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}


void CNewImage::Init()
{
}


void CNewImage::CreateControls()
{
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemBoxSizer2);

	m_rbDFI = new wxRadioButton(this, ID_RBDFI, _T("DFI"));
	itemBoxSizer2->Add(m_rbDFI, 1, wxEXPAND|wxALL, 5);
	m_rbD64 = new wxRadioButton(this, ID_RBD64, _T("D64"));
	itemBoxSizer2->Add(m_rbD64, 1, wxEXPAND|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxButton* itemButton5 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton6 = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	itemButton6->SetDefault();
}


void CNewImage::OnOK(wxCommandEvent& event)
{
	if (!(m_rbDFI->GetValue() || m_rbD64->GetValue()))
		return;
	if (m_rbDFI->GetValue())
		m_imageType = DFI;
	if (m_rbD64->GetValue())
		m_imageType = D64;
	event.Skip();
}


CbmImageType CNewImage::GetImageType()
{
	return m_imageType;
}
