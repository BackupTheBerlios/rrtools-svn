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

// #include "selectimage.h"

// Generated by DialogBlocks (unregistered), 16/10/2006 19:08:44

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "cbmimager.h"
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
////@end includes

#include "wx/image.h"
#include "wx/filedlg.h"
#include "wx/textctrl.h"
#include "wx/dnd.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/ffile.h"

#include "cbmimager.h"
#include "cbmimagerapp.h"
#include "selectimage.h"
#include "filednd.h"
#include "renamedialog.h"
#include "newimage.h"
#include "renamedisk.h"
#include "filesearcher.h"
#include "romcharset.h"
#include "hexeditor.h"
#include "bameditor.h"

#include "Logic/imagebase.h"
#include "Logic/d64image.h"
#include "Logic/dfiimage.h"
#include "Logic/d16image.h"
#include "Logic/cbmsector.h"
#include "Logic/cbmdirectoryentry.h"
#include "Logic/cbmdirectory.h"




////@begin XPM images
////@end XPM images

/*!
 * CBMImager type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CBMImager, wxFrame )


/*!
 * CBMImager event table definition
 */

BEGIN_EVENT_TABLE( CBMImager, wxFrame )

////@begin CBMImager event table entries
    EVT_MENU( ID_MENUFILENEW, CBMImager::OnMenufilenewClick )

    EVT_MENU( ID_MENUFILEOPEN, CBMImager::OnMenufileopenClick )

    EVT_MENU( ID_MENUFILESAVE, CBMImager::OnMenufilesaveClick )

    EVT_MENU( ID_MENUFILESAVEAS, CBMImager::OnMenufilesaveasClick )

	EVT_MENU( ID_MENUFILESEARCH, CBMImager::OnMenufilesearchClick )

    EVT_MENU( ID_MENUFILEEXIT, CBMImager::OnMenufileexitClick )

	EVT_MENU( ID_MENUEXTRAS_EDITFILE, CBMImager::OnMenuextrasEditFile )

	EVT_MENU( ID_MENUEXTRAS_EDITBAM, CBMImager::OnMenuextrasEditBam )

    EVT_LISTBOX_DCLICK( ID_LISTBOXFILES, CBMImager::OnListboxfilesDClick )

	EVT_CLOSE( CBMImager::OnClose )

	EVT_MENU(CMD_ADD_FILES, CBMImager::OnEvent)
	EVT_MENU(CMD_DELETE_FILES, CBMImager::OnEvent)
	EVT_MENU(CMD_EXTRACT_FILES, CBMImager::OnEvent)
	EVT_MENU(CMD_RENAME_FILE, CBMImager::OnEvent)
	EVT_MENU(CMD_SHIFT_UP, CBMImager::OnEvent)
	EVT_MENU(CMD_SEP_BEFORE, CBMImager::OnEvent)
	EVT_MENU(CMD_SEP_AFTER, CBMImager::OnEvent)
	EVT_MENU(CMD_CREATE_SUBDIR, CBMImager::OnEvent)
	EVT_MENU(CMD_RENAME_DISK, CBMImager::OnEvent)

	EVT_CONTEXT_MENU(CBMImager::OnContextMenu)

	EVT_ODLISTBOX_DRAG_EVENT(wxID_ANY, CBMImager::OnODListDrag)
////@end CBMImager event table entries

END_EVENT_TABLE()

/*!
 * CBMImager constructors
 */

CBMImager::CBMImager( )
{
    Init();
}

CBMImager::CBMImager( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CBMImager creator
 */

bool CBMImager::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CBMImager creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end CBMImager creation
    return true;
}

/*!
 * Member initialisation 
 */

void CBMImager::Init()
{
    m_FileMenu = NULL;
    m_FileList = NULL;
    m_StatusBar = NULL;

	cbmImage = NULL;
	cbmDir = NULL;

	isDragSource = false;
}
/*!
 * Control creation for CBMImager
 */

void CBMImager::CreateControls()
{
	long style;
	wxSize size;
	wxLog *ptOldLogTarget;


	wxMenuBar* menuBar = new wxMenuBar;
	m_FileMenu = new wxMenu;
	m_FileMenu->Append(ID_MENUFILENEW, _("&New Image\tCtrl-N"), _T("Create a new empty image."), wxITEM_NORMAL);
	m_FileMenu->Append(ID_MENUFILEOPEN, _("&Open Image...\tCtrl-O"), _T("Open an existing image."), wxITEM_NORMAL);
	m_FileMenu->AppendSeparator();
	m_FileMenu->Append(ID_MENUFILESAVE, _("&Save Image\tCtrl-S"), _T("Save the current image."), wxITEM_NORMAL);
	m_FileMenu->Append(ID_MENUFILESAVEAS, _("Save Image as..."), _T("Save the current image with a different name."), wxITEM_NORMAL);
	m_FileMenu->AppendSeparator();
	m_FileMenu->Append(ID_MENUFILESEARCH, _("Sea&rch\tAlt-R"), _T("Search Files"), wxITEM_NORMAL);
	m_FileMenu->AppendSeparator();
	m_FileMenu->Append(ID_MENUFILEEXIT, _("E&xit\tAlt-X"), _T("Quit the application"), wxITEM_NORMAL);
	menuBar->Append(m_FileMenu, _("&File"));

	m_extrasMenu = new wxMenu;
	m_extrasMenu->Append(ID_MENUEXTRAS_EDITFILE, _("Edit &File"), _T("Edit the File-contents in a Hex-Editor"), wxITEM_NORMAL);
	m_extrasMenu->Append(ID_MENUEXTRAS_EDITBAM, _("Edit &BAM"), _T("Edit the BAM"), wxITEM_NORMAL);
	menuBar->Append(m_extrasMenu, _("&Extras"));
	SetMenuBar(menuBar);


	// create the sizers
	m_sizerMain = new wxBoxSizer(wxVERTICAL);

	// create the splitter and add a panel to each window
	style = wxSP_3D;
	m_splitter = new wxSplitterWindow(this);
	m_splitter->SetSashGravity(1.0);
	m_sizerMain->Add(m_splitter, 1, wxEXPAND);
	m_upperPanel = new wxPanel(m_splitter);
	m_lowerPanel = new wxPanel(m_splitter);
	size = m_splitter->GetClientSize();
	m_splitter->SplitHorizontally(m_upperPanel, m_lowerPanel, 3*size.GetHeight()/4);
	m_splitter->SetMinimumPaneSize(20);

	// set sizer for both windows
	m_upperBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	m_upperPanel->SetSizer(m_upperBoxSizer);
	m_lowerBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	m_lowerPanel->SetSizer(m_lowerBoxSizer);


	m_FileList = new CODListBox( m_upperPanel, ID_LISTBOXFILES, wxDefaultPosition, wxDefaultSize, wxLB_HSCROLL|wxLB_MULTIPLE|wxLB_NEEDED_SB );
	m_FileList->SetDropTarget(new DnDFile(this));
	m_upperBoxSizer->Add(m_FileList, 1, wxGROW);

	// create the message logger
	style = wxTE_MULTILINE|wxTE_READONLY;
	m_messageLog = new wxTextCtrl(m_lowerPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, style);
	m_lowerBoxSizer->Add(m_messageLog, 1, wxGROW);
	m_logTextCtrl = new wxLogTextCtrl(m_messageLog);

	m_StatusBar = new wxStatusBar( this, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
	m_StatusBar->SetFieldsCount(1);
	SetStatusBar(m_StatusBar);


	// activate new log target
	ptOldLogTarget = wxLog::SetActiveTarget(m_logTextCtrl);
	if( ptOldLogTarget!=NULL )
	{
		delete ptOldLogTarget;
	}
	// TODO: use compiler switches to select the settings below
	// these settings are for the DEBUG mode
	wxLog::SetVerbose(true);
	wxLog::SetLogLevel(wxLOG_Debug);
	// these settings are for release mode
	//wxLog::SetVerbose(false);
	//wxLog::SetLogLevel(wxLog::wxLOG_Verbose);


	wxLogMessage(_("Welcome to CBMImager V 0.1"));
	wxLogMessage(_("(w) 2006 Uncle Tom/DRM + Doc Bacardi/DRM."));

	m_FileList->SetCBMCharset(cbmRomCharset, CBM_ROMCHARSET_LENGTH);

	// Process CommandLine Arguments
	CbmImagerApp& theApp = wxGetApp();
	int argc = theApp.argc;
	wxChar** argv = theApp.argv;
	if (argc > 1)
	{
		wxString imageName = argv[1];
		OpenImage(imageName);
	}
}

/*!
 * Should we show tooltips?
 */

bool CBMImager::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CBMImager::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon CBMImager::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}
/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILENEW
 */

void CBMImager::OnMenuextrasEditFile(wxCommandEvent& event)
{
	byte *buffer;
	int sel;
	int fileLength;
	unsigned long cookie = 0;


	sel = m_FileList->GetFirstSelected(cookie);
	if (sel == wxNOT_FOUND)
	{
		return;
	}
	CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
	if (entry == NULL)
	{
		return;
	}

	if (entry->GetFileType() == CBM_DEL)
	{
		return;
	}
	try
	{
		fileLength = entry->GetFileContent(cbmImage, &buffer);
	}
	catch (char *text)
	{
		wxMessageDialog* dialog = new wxMessageDialog(this, wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
		dialog->ShowModal();
		dialog->Destroy();
		return;
	}
	CHexEditor dlg(this);
	wxString label;

	label = wxT("Hex Editor - Editing File : ") + CCbmImageBase::PET2String(entry->GetFileName(), 0, 16);
	dlg.SetLabel(label);
	dlg.GetHexControl()->SetCBMCharset(cbmRomCharset, CBM_ROMCHARSET_LENGTH);
	dlg.GetHexControl()->SetData(buffer, fileLength);
	if (dlg.ShowModal() == wxID_OK)
	{
		entry->OverwriteFileContent(cbmImage, buffer);
	}
	delete buffer;
	wxUnusedVar(event);
}


void CBMImager::OnMenuextrasEditBam(wxCommandEvent& event)
{
	wxUnusedVar(event);

	if (cbmImage == NULL)
		return;

	CBamEditor dlg(this);
	dlg.SetCbmCharset(cbmRomCharset, CBM_ROMCHARSET_LENGTH);
	dlg.SetCbmImage(cbmImage);
	dlg.ShowModal();
	ReadCbmDirectory();				// perhaps we made changes in the directory, so update it
}


void CBMImager::OnMenufilenewClick( wxCommandEvent& event )
{
	CNewImage dialog(this);
	if (dialog.ShowModal() == wxID_OK)
	{
		if (cbmImage != NULL)
			delete cbmImage;
		if (cbmDir != NULL)
			delete cbmDir;

		cbmImage = NULL;
		cbmDir = NULL;

		for (int i = 0; i < (int)bamStack.GetCount(); i++)
		{
			CCbmSector *sec = bamStack[i];
			delete sec;
		}
		bamStack.Clear();

		switch (dialog.GetImageType())
		{
			case DFI:
				cbmImage = new CDFIImage();
				break;
			case D64:
				cbmImage = new CD64Image();
				break;
		}
		ReadCbmDirectory();
	}
    event.Skip();
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILEOPEN
 */

void CBMImager::OnMenufileopenClick( wxCommandEvent& event )
{
 //   SelectImage* window = new SelectImage(this, ID_SELECTIMAGE, _("Select Image"));
	//if (window->ShowModal() == wxID_OK )
	//{
	//}
	//window->Destroy();

	wxFileDialog dialog(this, _T("Open an Image"), _T(""), _T(""), _T("D64 files (*.d64)|*.d64|DFI Files (*.dfi)|*.dfi|All Files (*.*)|*.*"), 0);
	if (dialog.ShowModal() == wxID_OK)
	{
		if (dialog.GetPath().IsEmpty())
		{
			wxLogMessage( _T("Returned empty string.") );
			return;
		}

		if (!wxFileExists(dialog.GetPath()))
		{
			wxLogMessage( _T("File doesn't exist.") );
			return;
		}
		OpenImage(dialog.GetPath().Trim());
	}
    event.Skip();
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILESAVE
 */

void CBMImager::OnMenufilesaveClick( wxCommandEvent& event )
{
	wxString sImagePath;


	if (cbmImage != NULL)
	{
		sImagePath = cbmImage->GetImagePath();
		if ( sImagePath.IsEmpty()==false )
		{
			wxFileDialog *fileDlg;
			wxFileName tFileName;
			wxString filter;

			tFileName.Assign(sImagePath);
			switch (cbmImage->GetImageType())
			{
				case DFI:
					filter = wxT("DFI Files (*.dfi)|*.dfi");
					break;
				case D64:
					filter = wxT("D64 Files (*.d64)|*.d64");
					break;
			}
			fileDlg = new wxFileDialog(this, _T("Save Image"), tFileName.GetPath(), tFileName.GetFullName(), filter, wxSAVE);
			if (fileDlg->ShowModal() == wxID_OK)
			{
				wxFFile f(fileDlg->GetPath(), wxT("wb"));
				if (f.IsOpened())
				{
					f.Write(cbmImage->GetRawImage(), cbmImage->GetImageLength());
					f.Close();
				}
			}
			fileDlg->Destroy();
		}
		else
			OnMenufilesaveasClick(event);
	}
    event.Skip();
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILESAVEAS
 */

void CBMImager::OnMenufilesaveasClick( wxCommandEvent& event )
{
	wxString sImagePath;


	if (cbmImage != NULL)
	{
		sImagePath = cbmImage->GetImagePath();
		if ( sImagePath.IsEmpty()==false )
		{
			wxFileDialog *fileDlg;
			wxString filter;
			switch (cbmImage->GetImageType())
			{
				case DFI:
					filter = wxT("DFI Files (*.dfi)|*.dfi");
					break;
				case D64:
					filter = wxT("D64 Files (*.d64)|*.d64");
					break;
			}
			fileDlg = new wxFileDialog(this, _T("Save Image"), _T(""), _T(""), filter, wxSAVE);
			if (fileDlg->ShowModal() == wxID_OK)
			{
				wxFFile f(fileDlg->GetPath(), wxT("wb"));
				if (f.IsOpened())
				{
					f.Write(cbmImage->GetRawImage(), cbmImage->GetImageLength());
					f.Close();
				}
			}
			fileDlg->Destroy();
		}
		else
			OnMenufilesaveClick(event);
	}
    event.Skip();
}


void CBMImager::OnMenufilesearchClick( wxCommandEvent& event)
{
	wxUnusedVar(event);
	CFileSearcher dlg(this);
	if (dlg.ShowModal() == wxID_OK)
	{
		OpenImage(dlg.GetSelectedFile());
	}
}


/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILEEXIT
 */

void CBMImager::OnMenufileexitClick( wxCommandEvent& event )
{
	Close(true);
	event.Skip();
}

/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_LISTBOXFILES
 */

void CBMImager::OnListboxfilesDClick( wxCommandEvent& event )
{
	int sel;
	unsigned long cookie = 0;
	sel = m_FileList->GetFirstSelected(cookie);
	if (sel != wxNOT_FOUND)
	{
		if (m_FileList->GetItem(sel)->Cmp(wxT("0 \"..\"")) == 0)				// Directory up ?
		{
			CCbmSector *sec = bamStack[bamStack.GetCount() - 1];
			bamStack.RemoveAt(bamStack.GetCount() - 1);
			cbmImage->InitBAM(sec->GetTrack(), sec->GetSector());
			delete sec;
			ReadCbmDirectory();
		}
		else
		{
			CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
			if (entry != NULL && entry->GetFileType() == CBM_DIR)					// Directory ?
			{
				try
				{
					CCbmSector *oldBam = cbmImage->GetBam();
					CCbmSector *sec = cbmImage->GetSector(oldBam->GetTrack(), oldBam->GetSector());		// Clone BAM
					bamStack.Add(sec);
					cbmImage->InitBAM(entry->GetFileStartTrack(), entry->GetFileStartSector());
					ReadCbmDirectory();
				}
				catch (char* text)
				{
					CCbmSector *sec = bamStack[bamStack.GetCount() -1];
					cbmImage->InitBAM(sec->GetTrack(), sec->GetSector());			// Restore previous BAM
					delete sec;
					bamStack.RemoveAt(bamStack.GetCount() -1);
					wxMessageDialog* dialog = new wxMessageDialog(this, wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
					dialog->ShowModal();
					dialog->Destroy();
					return;
				}
				catch (...) {}
			}
		}
	}
    event.Skip();
}

// TODO: Implement hexdump for files / bam / sectors
void CBMImager::OnContextMenu(wxContextMenuEvent& event)
{
	unsigned long cookie = 0;
	wxUnusedVar(event);
	wxMenu menu(0);


	if( cbmImage==NULL )
	{
		return;
	}

	menu.Append(CMD_ADD_FILES, wxT("Add File(s)"));
	menu.Append(CMD_DELETE_FILES, wxT("Delete File(s)"));
	menu.Append(CMD_EXTRACT_FILES, wxT("Extract File(s)"));
	menu.AppendSeparator();
	menu.Append(CMD_RENAME_FILE, wxT("Rename File"));

	if (cbmImage->GetImageType() == DFI)
	{
		menu.AppendSeparator();
		menu.Append(CMD_CREATE_SUBDIR, wxT("Create Directory"));
	}

	if (m_FileList->GetItemCount() == 0)
		return;

	if (m_FileList->GetSelectedCount() == 1)
	{
		int sel = m_FileList->GetFirstSelected(cookie);
		if (m_FileList->GetEntry(sel) != NULL)
		{
			menu.AppendSeparator();
			menu.Append(CMD_SHIFT_UP, wxT("Shift Up"));
			menu.Append(CMD_SEP_BEFORE, wxT("Separator before"));
			menu.Append(CMD_SEP_AFTER, wxT("Separator after"));
		}
		if (m_FileList->IsSelected(0))
		{
			menu.AppendSeparator();
			menu.Append(CMD_RENAME_DISK, wxT("Rename Disk"));
		}
	}

	if (m_FileList->GetSelectedCount() == 0)
	{
			menu.Enable(CMD_DELETE_FILES, false);
			menu.Enable(CMD_EXTRACT_FILES, false);
			menu.Enable(CMD_RENAME_FILE, false);
	}
	for (int i = 0; i < (int)m_FileList->GetItemCount(); i++)
	{
		// Items without DirectoryEntry can't be extracted/deleted/renamed
		if (m_FileList->IsSelected(i) && m_FileList->GetEntry(i) == NULL)
		{
			menu.Enable(CMD_DELETE_FILES, false);
			menu.Enable(CMD_EXTRACT_FILES, false);
			menu.Enable(CMD_RENAME_FILE, false);
		}
		// D16 Images are Read-Only ! (for now)
		if (cbmImage->GetImageType() == D16)
		{
			menu.Enable(CMD_DELETE_FILES, false);
			menu.Enable(CMD_ADD_FILES, false);
		}
		// Directorys can't be extracted
		if (m_FileList->IsSelected(i) && m_FileList->GetEntry(i) != NULL && m_FileList->GetEntry(i)->GetFileType() == CBM_DIR)
		{
			menu.Enable(CMD_EXTRACT_FILES, false);
		}
	}
	if (m_FileList->GetSelectedCount() > 1)
		menu.Enable(CMD_RENAME_FILE, false);

	m_FileList->PopupMenu(&menu);
}


void CBMImager::OnODListDrag(wxCommandEvent& event)
{
	unsigned long cookie = 0;
	int sel;
	CCbmDirectoryEntry *entry = NULL;
	wxString sTempDir;


	wxUnusedVar(event);

	wxFileDataObject fData;
	
	sel = m_FileList->GetFirstSelected(cookie);
	if (sel == wxNOT_FOUND)
	{
		return;						// Nothing to Drag
	}

	itemUnderCursor = -1;
	while (sel != wxNOT_FOUND)
	{
		entry = m_FileList->GetEntry(sel);
		if (entry != NULL)
		{
			wxString str;
			wxString ext;
			wxString sIllChars;
			int iCnt;
			wxFileName fileName;
			int i;


			// does a temp dir already exist?
			if( sTempDir.IsEmpty()==true )
			{
				// no -> create a new temp file
				fileName.AssignTempFileName(wxT("CBMImager_"));
				// test result
				if( fileName.IsOk()==false )
				{
					// failed to create the temp file, cannot drag anything
					return;
				}
				// delete the temp file
				wxRemoveFile(fileName.GetFullPath());
				// remove any extension of the temp file name
				fileName.ClearExt();
				// set the filename as a new directory element
				fileName.AppendDir( fileName.GetName() );
				// get the complete path
				sTempDir = fileName.GetPath();
				// create the new directory
				wxMkdir(sTempDir);
			}

			// convert the filename to a string
			str = CCbmImageBase::PET2String(entry->GetFileName(), 0, 16);

			// get the forbidden chars for a filename
			sIllChars = fileName.GetForbiddenChars();
			sIllChars += fileName.GetPathSeparators();
			sIllChars += fileName.GetVolumeSeparator();
			// replace all forbidden chars in the filename
			for(iCnt = 0; iCnt < (int)sIllChars.Length(); ++iCnt)
			{
				str.Replace(sIllChars.Mid(iCnt, 1), wxT("_"), true);
			}

			ext = wxString::FromAscii(entry->GetFileTypeString());

			fileName.Assign(sTempDir, str, ext);
			wxString fname = fileName.GetFullPath().Trim();
			ExtractFile(entry, fileName.GetFullPath().Trim());
			fData.AddFile(fname);
			// Add the Filename to the list of temporary files. The files will be deleted, when the Program terminates
			for (i = 0; i < (int)usedTempFiles.Count(); i++)
			{
				if (usedTempFiles[i] == fname)			// don't add the filename, if it already exist in the list
					break;
			}
			if (i == (int)usedTempFiles.Count())
				usedTempFiles.Add(fname);
		}
		sel = m_FileList->GetNextSelected(cookie);
	}

	wxDropSource dragSource(this);
	dragSource.SetData(fData);
	isDragSource = true;			// We're currently acting as a DragSource
	wxDragResult result = dragSource.DoDragDrop( TRUE );
	if (result == wxDragNone)		// We probably moved the entry in our window, so move it inside the list
	{
		wxPoint pt = wxGetMousePosition();
		pt = m_FileList->ScreenToClient(pt);
		int item = m_FileList->HitTest(pt.x, pt.y);
		if (item != wxNOT_FOUND)
		{
			CCbmDirectoryEntry *targetEntry = m_FileList->GetEntry(item);
			if (targetEntry != NULL && entry != NULL)
			{
				cbmDir->MoveEntry(cbmImage, entry->GetEntryIndex(), targetEntry->GetEntryIndex());
				ReadCbmDirectory();
			}
		}
	}

	isDragSource = false;
}


//
// Eigene Funktionen
//


void CBMImager::SetItemUnderCursor(int index)
{ 
	itemUnderCursor = index;
	wxLogMessage(wxT("Item: %d"), index);
}


void CBMImager::OnClose(wxCloseEvent& event)
{
	if (cbmImage != NULL)
		delete cbmImage;
	if (cbmDir != NULL)
		delete cbmDir;
	for (int i = 0; i < (int)bamStack.GetCount(); i++)
	{
		CCbmSector *sec = bamStack[i];
		delete sec;
	}
	bamStack.Clear();

	// Delete Temporary files
    size_t nFiles = usedTempFiles.Count();
    for ( size_t n = 0; n < nFiles; n++ ) 
	{
		wxRemoveFile(usedTempFiles[n]);
    }

	this->Destroy();
	wxUnusedVar(event);
}


void CBMImager::OpenImage(wxString& fileName)
{
	if (cbmImage != NULL)
		delete cbmImage;
	if (cbmDir != NULL)
		delete cbmDir;

	cbmImage = NULL;
	cbmDir = NULL;

	// Clear BAM-Stack
	for (int i = 0; i < (int)bamStack.GetCount(); i++)
	{
		CCbmSector *sec = bamStack[i];
		delete sec;
	}
	bamStack.Clear();

	wxString ext = fileName.AfterLast('.');
	if (!ext.CmpNoCase(wxT("dfi")))
		cbmImage = new CDFIImage();
	else if (!ext.CmpNoCase(wxT("d64")))
		cbmImage = new CD64Image();
	else
		cbmImage = new CD16Image();
	if (cbmImage->Load(fileName))
		ReadCbmDirectory();

	m_StatusBar->SetStatusText(fileName);
}


void CBMImager::ReadCbmDirectory()
{
	const unsigned char *pcString;
	int iCnt;
	wxArrayString badFiles;						// for storing the names of "bad" files
	int iEntryCnt;
	int i;


	if (cbmImage == NULL)
		return;

	m_FileList->DeselectAll();
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
		wxMessageDialog* dialog = new wxMessageDialog(NULL, wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
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
	if (bamStack.GetCount() > 0)					// Add Parent Directory
	{
		str.Printf(wxT("0 \"..\""));
		m_FileList->AddItem(str, NULL);
	}
	iEntryCnt = cbmDir->GetEntryCount();
	for (i = 0; i < iEntryCnt; i++)
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

		if (entry->GetScratchProtected())
		{
			item.Append(wxT("<"));
		}

		if (!entry->GetClosedProperly())
		{
			item.Append(wxT("*"));
		}
		m_FileList->AddItem(item, entry);

		// Check for bad files and store their names
		if (entry->WasCircularLinked())
		{
			badFiles.Add(wxString::FromAscii((char*)entry->GetFileName()));
		}
	}
	str.Printf(wxT("%d BLOCKS FREE"), cbmImage->GetBlocksFree());
	m_FileList->AddItem(str, NULL);

	// Display a message, when bad files were encountered
	if (badFiles.Count() > 0)
	{
		wxString msg;
		msg.Printf(wxT("WARNING: Circular link detected in following File(s) :"));
		for (i = 0; i < (int)badFiles.Count(); i++)
		{
#ifdef __WIN32__
			msg.Append(wxString::FromAscii("\r\n"));		// Newline
#else
			msg.Append(wxString::FromAscii("\n"));			// is this correct ?
#endif
			msg.Append(badFiles[i]);
		}
#ifdef __WIN32__
		msg.Append(wxString::FromAscii("\r\n"));		// Newline
#else
		msg.Append(wxString::FromAscii("\n"));			// is this correct ?
#endif
		msg.Append(wxT("This may be a corrupted Image. The error is fixed, you should re-save this file"));
		wxMessageDialog* dialog = new wxMessageDialog(this, msg, wxT("CBMImager"), wxOK | wxICON_WARNING);
		dialog->ShowModal();
		dialog->Destroy();
	}
}


void CBMImager::AddFile(wxString& filename)
{
	int track = 0, sector = 0, readBytes;
	int newTrack = 0, newSector = 0;
	byte buffer[256];
	CCbmDirectoryEntry *entry = NULL;

	wxFFile f(filename, wxT("rb"));
	if (!f.IsOpened())
		return;

	if (!cbmImage->GetNextFreeSector(1, 0, &track, &sector))
	{
		wxMessageDialog* dialog = new wxMessageDialog(this,
			wxT("Disk full"), wxT("CBMImager"), wxOK | wxICON_ERROR);
		dialog->ShowModal();
		dialog->Destroy();
		return;
	}
	wxString fName = filename.AfterLast('\\');
	fName = fName.Left(16);
	try
	{
		entry = cbmDir->CreateNewEntry(cbmImage, fName.mb_str());
	}
	catch (char *text)
	{
		wxMessageDialog* dialog = new wxMessageDialog(this,
			wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
		dialog->ShowModal();
		dialog->Destroy();
		if (entry != NULL)
			delete entry;
		return;
	}

	entry->SetFileStartTrack(track);
	entry->SetFileStartSector(sector);
	readBytes = f.Read(&buffer[2], 254);
	while (readBytes > 0)
	{
		entry->SetBlocksUsed(entry->GetBlocksUsed() + 1);
		if (!cbmImage->AllocateSector(track, sector))
		{
			wxMessageDialog* dialog = new wxMessageDialog(this,
				wxT("Disk full"), wxT("CBMImager"), wxOK | wxICON_ERROR);
			dialog->ShowModal();
			dialog->Destroy();
			entry->DeleteFile(cbmImage);			// delete incomplete File
			delete entry;
			return;
		}
		if (readBytes < 254)						// End of Input-File ?
		{
			buffer[0] = 0;
			buffer[1] = (byte)(readBytes + 1);		// Mark End of File
		}
		else
		{
			if (!cbmImage->GetNextFreeSector(track, sector, &newTrack, &newSector))
			{
				wxMessageDialog* dialog = new wxMessageDialog(this,
					wxT("Disk full"), wxT("CBMImager"), wxOK | wxICON_ERROR);
				dialog->ShowModal();
				dialog->Destroy();
				entry->DeleteFile(cbmImage);		// delete incomplete File
				delete entry;
				return;
			}
			buffer[0] = (byte)newTrack;
			buffer[1] = (byte)newSector;
		}
		CCbmSector *sec = new CCbmSector(buffer);
		sec->SetTrack(track);
		sec->SetSector(sector);
		cbmImage->WriteSector(sec);
		delete sec;
		track = buffer[0];
		sector = buffer[1];
		memset(buffer, 0, 256);						// Clear buffer before the next Read-Action
		readBytes = f.Read(&buffer[2], 254);
	}
	f.Close();
	entry->Write(cbmImage);
	delete entry;

	ReadCbmDirectory();
}


void CBMImager::ExtractFile(CCbmDirectoryEntry *entry, wxString& fileName)
{
	CCbmSector *sec = NULL;
	int track = entry->GetFileStartTrack();
	int sector = entry->GetFileStartSector();
	wxFFile f(fileName, wxT("wb"));
	if (!f.IsOpened())
		return;
	while (track != 0)
	{
		try
		{
			sec = cbmImage->GetSector(track, sector);
			if (sec->GetNextTrack() != 0)
				f.Write(&sec->GetRawSector()[2], 254);
			else
				f.Write(&sec->GetRawSector()[2], sec->GetNextSector() - 1);
			track = sec->GetNextTrack();
			sector = sec->GetNextSector();
			delete sec;
			sec = NULL;
		}
		catch (char *text)
		{
			wxMessageDialog* dialog = new wxMessageDialog(this,
				wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
			dialog->ShowModal();
			dialog->Destroy();
			break;
		}
		catch (...) 
		{
			break;
		}
	}
	if (sec != NULL)
		delete sec;
	f.Close();
}



//
// EventHandler for the ContextMenu
//


void CBMImager::OnEvent(wxCommandEvent& event)
{
	unsigned long cookie = 0;
	int sel = 0;
	wxFileDialog *fileDlg = NULL;

	switch (event.m_id)
	{
		case CMD_ADD_FILES:
			if (cbmImage->GetImageType() != D16)
			{
				fileDlg = new wxFileDialog(this, _T("Add File(s)"), _T(""), _T(""), _T("All Files (*.*)|*.*"),
					wxOPEN | wxMULTIPLE);
				if (fileDlg->ShowModal() == wxID_OK)
				{
					wxArrayString filenames;
					fileDlg->GetPaths(filenames);
					for (int i = 0; i < (int)filenames.Count(); i++)
						AddFile(filenames[i]);
				}
				fileDlg->Destroy();
			}
			break;
		case CMD_DELETE_FILES:
			if (cbmImage->GetImageType() != D16)
			{
				for (int i = m_FileList->GetItemCount() - 1; i >= 0; i--)
				{
					if (m_FileList->IsSelected(i))
					{
						CCbmDirectoryEntry *entry = m_FileList->GetEntry(i);
						if (entry->GetFileType() == CBM_DIR)		// is this a Sub-Directory ?
						{
							try
							{
								if (cbmDir->GetFileCount(cbmImage, entry) > 0)
								{
									wxMessageDialog* dialog = new wxMessageDialog(this,
										wxT("Directory is not empty !"), wxT("CBMImager - can't delete"), wxICON_ERROR | wxOK);
									dialog->ShowModal();
									dialog->Destroy();
									return;
								}
							}
							catch (char* text)
							{
								wxMessageDialog* dialog = new wxMessageDialog(NULL, wxString::FromAscii(text), wxT("CBMImager"), wxOK | wxICON_ERROR);
								dialog->ShowModal();
								dialog->Destroy();
								continue;
							}
						}
						entry->DeleteFile(cbmImage);
						if ((entry->GetEntryIndex() + 1) == cbmDir->GetEntryCount())
						{	// If this is the very last Entry of the Directory, delete it "really"
							entry->SetFileStartTrack(0);
							entry->SetFileStartSector(0);
							entry->SetFileType(0);
							entry->Write(cbmImage);
							cbmDir->RemoveEntry(entry->GetEntryIndex());
							delete entry;
						}
					}
				}
				ReadCbmDirectory();
			}
			break;
		case CMD_EXTRACT_FILES:
			sel = m_FileList->GetFirstSelected(cookie);
			while (sel != wxNOT_FOUND)
			{
				CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
				wxString str;
				str.Printf(wxT("%s.%s"), entry->GetFileName(), entry->GetFileType());
				fileDlg = new wxFileDialog(this, _T("Add File(s)"), _T(""), str, _T("All Files (*.*)|*.*"),
					wxSAVE);
				if (fileDlg->ShowModal() == wxID_OK)
				{
					wxString fName = fileDlg->GetPath();
					ExtractFile(entry, fName);
				}
				fileDlg->Destroy();
				sel = m_FileList->GetNextSelected(cookie);
			}
			break;
		case CMD_RENAME_FILE:
			sel = m_FileList->GetFirstSelected(cookie);
			if (sel != wxNOT_FOUND)
			{
				unsigned char aucBuffer[17];
				wxString sFileName;


				CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
				sFileName = CCbmImageBase::PET2String(entry->GetFileName(), 0, 16);
				CRenameDialog dialog(this, sFileName);
				if (dialog.ShowModal() == wxID_OK)
				{
					entry->SetFileName(CCbmImageBase::ASCII2PET(dialog.GetText().mb_str(), 16, aucBuffer));
					entry->Write(cbmImage);
					ReadCbmDirectory();
				}
			}
			break;
		case CMD_RENAME_DISK:
			if (m_FileList->GetSelectedCount() == 1)		// should always be 1, because this is checked in OnContextMenu()
			{
				unsigned char aucBuffer[17];
				wxString sDiskName;
				wxString sDiskId;


				sDiskName = CCbmImageBase::PET2String(cbmDir->GetDiskName(), 0, 16);
				sDiskId = CCbmImageBase::PET2String(cbmDir->GetDiskID(), 0, 5);

				CRenameDisk dlg(this);
				dlg.m_DiskName->SetValue(sDiskName);
				dlg.m_DiskID->SetValue(sDiskId);

				if (dlg.ShowModal() == wxID_OK)
				{
					cbmImage->SetDiskName(CCbmImageBase::ASCII2PET(dlg.m_DiskName->GetValue().mb_str(), 16, aucBuffer));
					cbmImage->SetDiskID(CCbmImageBase::ASCII2PET(dlg.m_DiskID->GetValue().mb_str(), 5, aucBuffer));
					ReadCbmDirectory();
				}
			}
			break;
		case CMD_SHIFT_UP:
			sel = m_FileList->GetFirstSelected(cookie);
			if (sel != wxNOT_FOUND && sel > 0)
			{
				CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
				CCbmDirectoryEntry *prevEntry = m_FileList->GetEntry(sel - 1);
				if (prevEntry != NULL && prevEntry->GetFileType() != CBM_DEL)		// Previous Entry must be of type DEL
				{
					wxMessageDialog* dialog = new wxMessageDialog(this,
						wxT("Previous Entry must be of type DEL !"), wxT("CBMImager - can't shift up"), wxOK | wxICON_ERROR);
					dialog->ShowModal();
					dialog->Destroy();
					return;
				}
				if (entry != NULL)
					cbmDir->ShiftEntries(cbmImage, entry->GetEntryIndex(), false);
				ReadCbmDirectory();
			}
			break;
		case CMD_SEP_BEFORE:
			sel = m_FileList->GetFirstSelected(cookie);
			if (sel != wxNOT_FOUND)
			{
				CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
				if (entry != NULL)
					cbmDir->ShiftEntries(cbmImage, entry->GetEntryIndex(), true);
				ReadCbmDirectory();
			}
			break;
		case CMD_SEP_AFTER:
			sel = m_FileList->GetFirstSelected(cookie);
			if (sel != wxNOT_FOUND)
			{
				CCbmDirectoryEntry *entry = m_FileList->GetEntry(sel);
				if (entry != NULL)
					cbmDir->ShiftEntries(cbmImage, entry->GetEntryIndex() + 1, true);
				ReadCbmDirectory();
			}
			break;
		case CMD_CREATE_SUBDIR:
				CRenameDialog dialog(this, wxT("NEW DIR"));
				if (dialog.ShowModal() == wxID_OK)
				{
					if (cbmDir->CreateSubDirectory(cbmImage, dialog.GetText().mb_str()))
						ReadCbmDirectory();
					else
					{
						wxMessageDialog* dialog = new wxMessageDialog(this,
							wxT("Failed to create Directory"), wxT("CBMImager"), wxOK | wxICON_ERROR);
						dialog->ShowModal();
						dialog->Destroy();
					}
				}
			break;
	}
}


CbmImageType CBMImager::GetCurrentImageType()
{
	if (cbmImage != NULL)
		return cbmImage->GetImageType();
	return NONE;
}


bool CBMImager::IsDragSource()
{
	return isDragSource;
}

