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

// Generated by DialogBlocks (unregistered), 30/10/2006 18:02:59

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "trackeditor.h"
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
#include "trackeditor.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * CTrackEditor type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CTrackEditor, wxDialog )

/*!
 * CTrackEditor event table definition
 */

BEGIN_EVENT_TABLE( CTrackEditor, wxDialog )

////@begin CTrackEditor event table entries
    EVT_BUTTON( ID_BUTTON1, CTrackEditor::OnButtonPrevLogical )

    EVT_BUTTON( ID_BUTTON2, CTrackEditor::OnButtonPrevLinked )

    EVT_BUTTON( ID_BUTTON3, CTrackEditor::OnButtonNextLogical )

    EVT_BUTTON( ID_BUTTON4, CTrackEditor::OnButtonNextLinked )

    EVT_BUTTON( ID_BUTTON5, CTrackEditor::OnButtonApply )

	EVT_CLOSE( CTrackEditor::OnClose )

////@end CTrackEditor event table entries

END_EVENT_TABLE()

/*!
 * CTrackEditor constructors
 */

CTrackEditor::CTrackEditor( )
{
    Init();
}

CTrackEditor::CTrackEditor( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CTrackEditor creator
 */

bool CTrackEditor::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CTrackEditor creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CTrackEditor creation
    return true;
}

/*!
 * Member initialisation 
 */

void CTrackEditor::Init()
{
////@begin CTrackEditor member initialisation
    m_hexList = NULL;
	currentSector = NULL;
////@end CTrackEditor member initialisation
}
/*!
 * Control creation for CTrackEditor
 */

void CTrackEditor::CreateControls()
{    
////@begin CTrackEditor content construction
    // Generated by DialogBlocks, 30/10/2006 18:02:59 (unregistered)

    CTrackEditor* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    m_hexList = new CHexControl( itemDialog1 );
	m_hexList->SetSize(330, 270);
    itemBoxSizer2->Add(m_hexList, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Navigation"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Previous"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxVERTICAL);
	itemStaticBoxSizer4->Add(itemStaticBoxSizer5, 0, wxALIGN_BOTTOM|wxALL, 5);

    btnPrevLogical = new wxButton( itemDialog1, ID_BUTTON1, _("Logical"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer5->Add(btnPrevLogical, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    btnPrevLinked = new wxButton( itemDialog1, ID_BUTTON2, _("Linked"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer5->Add(btnPrevLinked, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer8Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Next"));
    wxStaticBoxSizer* itemStaticBoxSizer8 = new wxStaticBoxSizer(itemStaticBoxSizer8Static, wxVERTICAL);
    itemStaticBoxSizer4->Add(itemStaticBoxSizer8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    btnNextLogical = new wxButton( itemDialog1, ID_BUTTON3, _("Logical"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer8->Add(btnNextLogical, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    btnNextLinked = new wxButton( itemDialog1, ID_BUTTON4, _("Linked"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer8->Add(btnNextLinked, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton *btnApply = new wxButton( itemDialog1, ID_BUTTON5, _("Apply Changes"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(btnApply, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end CTrackEditor content construction
}

void CTrackEditor::OnClose(wxCloseEvent& event)
{
	if (currentSector != NULL)
		delete currentSector;
	currentSector = NULL;

	event.Skip();
}

void CTrackEditor::OnButtonApply(wxCommandEvent& event)
{
	if (currentSector != NULL && cbmImage != NULL)
		cbmImage->WriteSector(currentSector);
	event.Skip();
}



void CTrackEditor::OnButtonPrevLogical( wxCommandEvent& event )
{
	if (m_sector > 0)
		m_sector--;
	else
	{
		m_track--;
		m_sector = CCbmImageBase::GetSectorCount(m_track, cbmImage->GetImageType()) - 1;
	}
	DisplaySector();
    event.Skip();
}


void CTrackEditor::OnButtonPrevLinked( wxCommandEvent& event )
{
	m_track = m_prevTrack;
	m_sector = m_prevSector;
	DisplaySector();
    event.Skip();
}


void CTrackEditor::OnButtonNextLogical( wxCommandEvent& event )
{
	if ((m_sector + 1) < CCbmImageBase::GetSectorCount(m_track, cbmImage->GetImageType()))
		m_sector++;
	else
	{
		m_track++;
		m_sector = 0;
	}
	DisplaySector();
    event.Skip();
}


void CTrackEditor::OnButtonNextLinked( wxCommandEvent& event )
{
	m_track = currentSector->GetRawSector()[0];
	m_sector = currentSector->GetRawSector()[1];

	DisplaySector();
    event.Skip();
}



/*!
 * Should we show tooltips?
 */

bool CTrackEditor::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CTrackEditor::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CTrackEditor bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CTrackEditor bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CTrackEditor::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CTrackEditor icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CTrackEditor icon retrieval
}



void CTrackEditor::SetCbmImage(CCbmImageBase *image)
{
	cbmImage = image;
}

void CTrackEditor::SetCbmCharset(byte* buffer, int nLength)
{
	m_hexList->SetCBMCharset(buffer, nLength);
}

void CTrackEditor::SetStartInfo(int track, int sector)
{
	m_track = track;
	m_sector = sector;
	DisplaySector();
}

void CTrackEditor::DisplaySector()
{
	if (currentSector != NULL)
		delete currentSector;
	currentSector = NULL;

	currentSector = cbmImage->GetSector(m_track, m_sector);
	m_hexList->SetData(currentSector->GetRawSector(), 256);
	m_hexList->Refresh();
	EnableButtons();

	wxString label;
	label.Printf(wxT("Track Editor - Editing Track / Sector : %d, %d"), m_track, m_sector);
	SetLabel(label);
}


void CTrackEditor::EnableButtons()
{
	int track, sector;
	bool found = false;

	btnNextLinked->Enable(true);
	btnNextLogical->Enable(true);
	btnPrevLinked->Enable(true);
	btnPrevLogical->Enable(true);

	// first sector ?
	if (m_track == 1 && m_sector == 0)
		btnPrevLogical->Enable(false);
	// last sector ?
	if (m_track == cbmImage->GetNumTracks() && m_sector == CCbmImageBase::GetSectorCount(m_track, cbmImage->GetImageType()))
		btnNextLogical->Enable(false);
	// link to valid next sector ?
	track = currentSector->GetRawSector()[0];
	sector = currentSector->GetRawSector()[1];
	if (!(track > 0 && track <= cbmImage->GetNumTracks() && (sector + 1) < CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType())))
		btnNextLinked->Enable(false);
	// search link to current sector
	track = 1;
	sector = 0;
	while (!found)
	{
		CCbmSector *sec = cbmImage->GetSector(track, sector);
		if (sec->GetNextTrack() == currentSector->GetTrack() && sec->GetNextSector() == currentSector->GetSector())
			found = true;
		else
		{
			if ((sector + 1) < CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType()))
				sector++;
			else
			{
				track++;
				sector = 0;
				if (track > cbmImage->GetNumTracks())
				{
					delete sec;
					break;
				}
			}
		}
		delete sec;
	}
	if (!found)
		btnPrevLinked->Enable(false);
	else
	{
		m_prevTrack = track;
		m_prevSector = sector;			// store info for "previous linked"
	}
}
