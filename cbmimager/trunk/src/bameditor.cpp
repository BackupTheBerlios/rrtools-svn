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

// Generated by DialogBlocks (unregistered), 29/10/2006 21:08:30

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
#include "bameditor.h"
#include "trackeditor.h"
#include "cbmimager_id.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * CBamEditor type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CBamEditor, wxDialog )

/*!
 * CBamEditor event table definition
 */

BEGIN_EVENT_TABLE( CBamEditor, wxDialog )

	EVT_ODLISTBOX_SELECTION_EVENT( wxID_ANY, CBamEditor::OnFileSelected )
	EVT_CLOSE( CBamEditor::OnClose )
	EVT_CONTEXT_MENU( CBamEditor::OnContextMenu )
	EVT_MENU(CMD_EDIT_SECTOR, CBamEditor::OnContextMenuEvent)
	EVT_MENU(CMD_EDIT_DIR, CBamEditor::OnContextMenuEvent)
	EVT_BAMCONTROL_SELECTION_EVENT(wxID_ANY, CBamEditor::OnSectorSelected)

END_EVENT_TABLE()

/*!
 * CBamEditor constructors
 */

CBamEditor::CBamEditor( )
{
    Init();
}

CBamEditor::CBamEditor( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CBamEditor creator
 */

bool CBamEditor::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CBamEditor creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CBamEditor creation
    return true;
}

/*!
 * Member initialisation 
 */

void CBamEditor::Init()
{
////@begin CBamEditor member initialisation
    m_BamList = NULL;
    m_trackSector = NULL;
    m_FileList = NULL;

	cbmImage = NULL;
	cbmDir = NULL;
////@end CBamEditor member initialisation
}
/*!
 * Control creation for CBamEditor
 */

void CBamEditor::CreateControls()
{    
////@begin CBamEditor content construction
    // Generated by DialogBlocks, 29/10/2006 21:08:30 (unregistered)

    CBamEditor* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("BAM"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_BamList = new CBamControl( itemDialog1 );
    itemStaticBoxSizer4->Add(m_BamList, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer6, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Track / Sector :"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    itemBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    m_trackSector = new wxStaticText( itemDialog1, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(m_trackSector, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxStaticBox* itemStaticBoxSizer9Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Files"));
	wxStaticBoxSizer* itemStaticBoxSizer9 = new wxStaticBoxSizer(itemStaticBoxSizer9Static, wxHORIZONTAL);
    itemBoxSizer3->Add(itemStaticBoxSizer9, 0, wxEXPAND|wxALL, 5);

    m_FileList = new CODListBox( itemDialog1 );
	m_FileList->SetSize(250, 200);
    itemStaticBoxSizer9->Add(m_FileList, 0, wxEXPAND|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end CBamEditor content construction
}

/*!
 * Should we show tooltips?
 */

bool CBamEditor::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CBamEditor::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CBamEditor bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CBamEditor bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CBamEditor::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CBamEditor icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CBamEditor icon retrieval
}


void CBamEditor::OnClose(wxCloseEvent& event)
{
	if (cbmDir != NULL)
	{
		delete cbmDir;
		cbmDir = NULL;
	}
	this->Destroy();

	wxUnusedVar(event);
}


void CBamEditor::OnContextMenu(wxContextMenuEvent& event)
{
	int track, sector;
	wxUnusedVar(event);

	if (event.GetId() == ID_BAMCONTROL)		// sender was the BAM-Control ?
	{
		m_BamList->GetCbmSelection(&track, &sector);
		if (track > 0 && sector >= 0)		// valid selection ?
		{
			wxMenu menu(0);
			menu.Append(CMD_EDIT_SECTOR, wxT("Edit Sector"));
			m_BamList->PopupMenu(&menu);
		}
	}
	else if (event.GetId() == ID_ODLISTBOX)
	{
		wxMenu menu(0);
		menu.Append(CMD_EDIT_DIR, wxT("Edit Directory"));
		m_BamList->PopupMenu(&menu);
	}
}


void CBamEditor::OnContextMenuEvent(wxCommandEvent& event)
{
	int track, sector;
	CTrackEditor dlg(this);

	switch (event.GetId())
	{
		case CMD_EDIT_SECTOR:
			m_BamList->GetCbmSelection(&track, &sector);
			dlg.SetCbmImage(cbmImage);
			dlg.SetCbmCharset(cbmCharset, charsetLength);
			dlg.SetStartInfo(track, sector);
			dlg.ShowModal();
			break;
		case CMD_EDIT_DIR:
			track = cbmImage->GetBam()->GetNextTrack();
			sector = cbmImage->GetBam()->GetNextSector();
			dlg.SetCbmImage(cbmImage);
			dlg.SetCbmCharset(cbmCharset, charsetLength);
			dlg.SetStartInfo(track, sector);
			dlg.ShowModal();
	}
	ReadCbmDirectory();				// perhaps we made changes in the directory, so update it
}


CBamControl *CBamEditor::GetBamControl()
{
	return m_BamList;
}



void CBamEditor::SetCbmImage(CCbmImageBase *image)
{
	cbmImage = image;
	m_BamList->SetImage(cbmImage);

	ReadCbmDirectory();
}


void CBamEditor::SetCbmCharset(byte* buffer, int nLength)
{
	m_FileList->SetCBMCharset(buffer, nLength);
	m_BamList->SetCBMCharset(buffer, nLength);
	cbmCharset = buffer;
	charsetLength = nLength;
}


void CBamEditor::ReadCbmDirectory()
{
	const unsigned char *pcString;
	int iCnt;

	if (cbmImage == NULL)
		return;

	m_FileList->Clear();

	if (cbmDir != NULL)
		delete cbmDir;
	cbmDir = NULL;

	try
	{
		cbmDir = new CCbmDirectory(cbmImage);
	}
	catch (char* text)
	{
		wxMessageDialog* dialog = new wxMessageDialog(NULL, wxString::FromAscii(text), wxT(CBMIMAGER_APPLICATION_NAME), wxOK | wxICON_ERROR);
		dialog->ShowModal();
		dialog->Destroy();
		return;
	}

	wxString str;
	pcString = (unsigned char*)cbmDir->GetDiskName();
	str = wxT("0 \"");
	for(iCnt = 0; iCnt < 16; ++iCnt)
	{
		str += pcString[iCnt];
	}
	str.Append(wxT("\" "));
	pcString = (unsigned char*)cbmDir->GetDiskID();
	for(iCnt = 0; iCnt < 5; ++iCnt)
	{
		str += pcString[iCnt];
	}
	
	m_FileList->AddItem(str, NULL);
	int cnt = cbmDir->GetEntryCount();
	for (int i = 0; i < cnt; i++)
	{
		CCbmDirectoryEntry *entry = cbmDir->GetEntry(i);
		wxString item;
		item.Printf(wxT("%-5d\""), entry->GetBlocksUsed());
		pcString = (unsigned char*)entry->GetFileName();
		for(iCnt = 0; iCnt < 16; ++iCnt)
		{
			item += pcString[iCnt];
		}
		item.Append(wxT("\" "));
		item.Append(wxString::FromAscii(entry->GetFileTypeString()));

		if (!entry->GetClosedProperly())
		{
			item.Append(wxT("*"));
		}
		m_FileList->AddItem(item, entry);
	}
	str.Printf(wxT("%d BLOCKS FREE"), cbmImage->GetBlocksFree());
	m_FileList->AddItem(str, NULL);
}


void CBamEditor::OnFileSelected(wxCommandEvent& event)
{
	unsigned long *fileSectors = NULL;
	int numSectors;

	int sel = m_FileList->GetSelection();
	if (sel != wxNOT_FOUND)
	{
		CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
		if (entry != NULL)
		{
			try
			{
				numSectors = GetFileSectors(entry, &fileSectors);
			}
			catch (char *text)
			{
				wxMessageDialog* dialog = new wxMessageDialog(NULL, wxString::FromAscii(text), wxT(CBMIMAGER_APPLICATION_NAME), wxOK | wxICON_ERROR);
				dialog->ShowModal();
				dialog->Destroy();
				return;
			}
			m_BamList->ClearFileSectors();					// Clear old Sectors
			for (int i = 0; i < numSectors; i++)
			{
				m_BamList->AddFileSector(fileSectors[i]);
			}
			if (fileSectors != NULL)
				delete fileSectors;
			m_BamList->Refresh();
			return;
		}
	}
	m_BamList->ClearFileSectors();
	m_BamList->Refresh();
	event.Skip();
}


void CBamEditor::OnSectorSelected(wxCommandEvent& event)
{
	int track, sector;

	m_BamList->GetCbmSelection(&track, &sector);
	wxString label;
	if (track == -1 || sector == -1)
		label = wxT("");
	else
		label.Printf(_T("%d, %d"), track, sector);
	m_trackSector->SetLabel(label);

	wxUnusedVar(event);
}


int CBamEditor::GetFileSectors(CCbmDirectoryEntry *entry, unsigned long **buffer)
{
	if (entry->GetBlocksUsedReal() == 0)
		return 0;

	unsigned long *fileSectors = new unsigned long[entry->GetBlocksUsedReal()];		// Allocate list
	int i = 0, track, sector;
	track = entry->GetFileStartTrack();
	sector = entry->GetFileStartSector();
	while (track > 0)
	{
		fileSectors[i] = (track << 16) + sector;
		CCbmSector *sec = cbmImage->GetSector(track, sector);
		track = sec->GetNextTrack();
		sector = sec->GetNextSector();
		delete sec;
		i++;
	}
	*buffer = fileSectors;
	return i;
}
