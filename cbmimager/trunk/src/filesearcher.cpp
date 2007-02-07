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

// Generated by DialogBlocks (unregistered), 28/10/2006 15:44:17

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "filesearcher.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


////@begin includes
#include "cbmimager_version.h"
#include "filesearcher.h"
#include "cbmimager.h"

#include "Logic/imagebase.h"
#include "Logic/d64image.h"
#include "Logic/dfiimage.h"
#include "Logic/d16image.h"
#include "Logic/cbmsector.h"
#include "Logic/cbmdirectoryentry.h"
#include "Logic/cbmdirectory.h"

#include "wx/dir.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * CFileSearcher type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CFileSearcher, wxDialog )

/*!
 * CFileSearcher event table definition
 */

BEGIN_EVENT_TABLE( CFileSearcher, wxDialog )

////@begin CFileSearcher event table entries
    EVT_BUTTON( ID_BUTTONSELECTPATH, CFileSearcher::OnButtonselectpathClick )

    EVT_BUTTON( ID_BUTTONSEARCH, CFileSearcher::OnButtonsearchClick )

    EVT_LISTBOX( ID_LISTBOXRESULTS, CFileSearcher::OnListboxresultsSelected )

////@end CFileSearcher event table entries

END_EVENT_TABLE()

/*!
 * CFileSearcher constructors
 */

CFileSearcher::CFileSearcher( )
{
    Init();
}

CFileSearcher::CFileSearcher( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CFileSearcher creator
 */

bool CFileSearcher::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CFileSearcher creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CFileSearcher creation
    return true;
}

/*!
 * Member initialisation 
 */

void CFileSearcher::Init()
{
////@begin CFileSearcher member initialisation
    m_searchFolder = NULL;
    m_searchText = NULL;
    m_exactSearch = NULL;
    m_resultsList = NULL;
////@end CFileSearcher member initialisation
}
/*!
 * Control creation for CFileSearcher
 */

void CFileSearcher::CreateControls()
{    
////@begin CFileSearcher content construction
    // Generated by DialogBlocks, 28/10/2006 16:38:48 (unregistered)

    CFileSearcher* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Search Folder:"), wxDefaultPosition, wxSize(75, -1), 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    m_searchFolder = new wxTextCtrl( itemDialog1, ID_TEXTCTRLPATH, _T(""), wxDefaultPosition, wxSize(250, -1), 0 );
    itemBoxSizer3->Add(m_searchFolder, 0, wxGROW|wxALL, 5);

    wxButton* itemButton6 = new wxButton( itemDialog1, ID_BUTTONSELECTPATH, _("..."), wxDefaultPosition, wxSize(23, -1), 0 );
    itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Search:"), wxDefaultPosition, wxSize(70, -1), 0 );
    itemBoxSizer7->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    m_searchText = new wxTextCtrl( itemDialog1, ID_TEXTCTRLSEARCH, _T(""), wxDefaultPosition, wxSize(150, -1), 0 );
    itemBoxSizer7->Add(m_searchText, 0, wxGROW|wxALL, 5);

    m_exactSearch = new wxCheckBox( itemDialog1, ID_CBEXACTSEARCH, _("Exact Search"), wxDefaultPosition, wxDefaultSize, 0 );
    m_exactSearch->SetValue(false);
    itemBoxSizer7->Add(m_exactSearch, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, ID_BUTTONSEARCH, _("GO!"), wxDefaultPosition, wxSize(31, -1), 0 );
    itemButton11->SetDefault();
    itemBoxSizer7->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer12Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Results"));
    wxStaticBoxSizer* itemStaticBoxSizer12 = new wxStaticBoxSizer(itemStaticBoxSizer12Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer12, 0, wxGROW|wxALL, 5);

    wxString* m_resultsListStrings = NULL;
    m_resultsList = new wxListBox( itemDialog1, ID_LISTBOXRESULTS, wxDefaultPosition, wxSize(-1, 200), 0, m_resultsListStrings, wxLB_SINGLE|wxLB_NEEDED_SB );
    itemStaticBoxSizer12->Add(m_resultsList, 2, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(itemButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_okButton = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer14->Add(m_okButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	m_okButton->Enable(false);

    m_statusBar = new wxStatusBar( itemDialog1, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
    m_statusBar->SetFieldsCount(1);
    itemBoxSizer2->Add(m_statusBar, 0, wxGROW|wxALL, 5);

////@end CFileSearcher content construction
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONSELECTPATH
 */

void CFileSearcher::OnButtonselectpathClick( wxCommandEvent& event )
{
	const wxString& result = wxDirSelector(wxT("Coose a Start-Folder"));
	if (!result.IsEmpty())
	{
		m_searchFolder->SetValue(result);
	}
    event.Skip();
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONSEARCH
 */

void CFileSearcher::OnButtonsearchClick( wxCommandEvent& event )
{
	wxArrayString filenames;
	int numImages = 0;
	CCbmImageBase *image = NULL;
	CCbmDirectory *dir = NULL;
	unsigned char buffer[17];

	if (m_searchFolder->GetValue().IsEmpty())
	{
		wxMessageDialog* dialog = new wxMessageDialog(this, wxT("Please select a Folder first"), wxT(CBMIMAGER_APPLICATION_NAME), wxOK | wxICON_WARNING);
		dialog->ShowModal();
		dialog->Destroy();
		return;
	}
	if (m_searchText->GetValue().IsEmpty())
	{
		wxMessageDialog* dialog = new wxMessageDialog(this, wxT("Nothing to search for"), wxT(CBMIMAGER_APPLICATION_NAME), wxOK | wxICON_WARNING);
		dialog->ShowModal();
		dialog->Destroy();
		return;
	}

	m_resultsList->DeselectAll();
	m_resultsList->Clear();

	size_t numFiles = wxDir::GetAllFiles(m_searchFolder->GetValue(), &filenames, wxT("*.*"));
	for (size_t i = 0; i < numFiles; i++)
	{
		wxString ext = filenames[i].AfterLast('.');
		if (ext.CmpNoCase(wxT("dfi")) == 0 || ext.CmpNoCase(wxT("d64")) == 0)
		{
			m_statusBar->SetStatusText(filenames[i]);
			numImages++;
			if (ext.CmpNoCase(wxT("dfi")) == 0)
			{
				image = new CDFIImage();
			}
			else if (ext.CmpNoCase(wxT("d64")) == 0)
			{
				image = new CD64Image();
			}
			if (image->Load(filenames[i]))
			{
				try
				{
					dir = new CCbmDirectory(image);
				}
				catch (...)
				{
					if (dir != NULL)
						delete dir;
					if (image != NULL)
						delete image;
					image = NULL;
					dir = NULL;
					continue;
				}
				if (dir->SearchFile(image, (char*)CCbmImageBase::ASCII2PET(m_searchText->GetValue().mb_str(), 16, buffer), !m_exactSearch->IsChecked()))
					m_resultsList->Append(filenames[i]);
			}
			delete dir;
			delete image;
			image = NULL;
			dir = NULL;
		}
	}
	wxString msg;
	msg.Printf(wxT("Search complete, %d Images scanned"), numImages);
	m_statusBar->SetStatusText(msg);
    event.Skip();
}

/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_LISTBOXRESULTS
 */

void CFileSearcher::OnListboxresultsSelected( wxCommandEvent& event )
{
	int sel = m_resultsList->GetSelection();
	if (sel != wxNOT_FOUND)
	{
		m_selectedFile = m_resultsList->GetString(sel);
		((CBMImager*)GetParent())->OpenImage(m_selectedFile);
		m_okButton->Enable(true);
	}
	else
		m_okButton->Enable(false);
    event.Skip();
}


/*!
 * Should we show tooltips?
 */

bool CFileSearcher::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CFileSearcher::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CFileSearcher bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CFileSearcher bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CFileSearcher::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CFileSearcher icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CFileSearcher icon retrieval
}


wxString& CFileSearcher::GetSelectedFile()
{
	return m_selectedFile;
}
