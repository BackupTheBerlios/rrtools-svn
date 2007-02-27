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

// Generated by DialogBlocks (unregistered), 16/10/2006 19:08:44

#ifndef _CBMIMAGER_H_
#define _CBMIMAGER_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "cbmimager.h"
#endif


/*!
 * Includes
 */

////@begin includes
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>

#include "cbmimager_id.h"

#include "odlistbox.h"

#include "Logic/imagebase.h"
#include "Logic/cbmdirectory.h"

////@end includes


WX_DEFINE_ARRAY(CCbmSector*, BAMStack);

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxMenu;
class wxStatusBar;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define SYMBOL_CBMIMAGER_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_CBMIMAGER_TITLE _("CBM Imager")
#define SYMBOL_CBMIMAGER_IDNAME ID_CBMIMAGER
#define SYMBOL_CBMIMAGER_SIZE wxSize(400, 300)
#define SYMBOL_CBMIMAGER_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * CBMImager class declaration
 */

class CBMImager: public wxFrame
{    
    DECLARE_DYNAMIC_CLASS( CBMImager )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CBMImager(void);
    CBMImager(wxWindow* parent, wxWindowID id = SYMBOL_CBMIMAGER_IDNAME, long style = SYMBOL_CBMIMAGER_STYLE);
    ~CBMImager(void);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CBMIMAGER_IDNAME, long style = SYMBOL_CBMIMAGER_STYLE );

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CBMImager event handler declarations

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILENEW
    void OnMenufilenewClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILEOPEN
    void OnMenufileopenClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILESAVE
    void OnMenufilesaveClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILESAVEAS
    void OnMenufilesaveasClick( wxCommandEvent& event );

	void OnMenufilesearchClick( wxCommandEvent& event);

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_MENUFILEEXIT
    void OnMenufileexitClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_LISTBOXFILES
    void OnListboxfilesDClick( wxCommandEvent& event );

	void OnMenuextrasEditFile( wxCommandEvent& event);
	void OnMenuextrasEditBam( wxCommandEvent& event);
    void OnMenuextrasImportT64( wxCommandEvent& event);

	void OnShowExtrasMenu( wxUpdateUIEvent& event);

	void OnClose(wxCloseEvent& event);

	void OnEvent(wxCommandEvent& event);

	void OnContextMenu(wxContextMenuEvent& event);

	void OnODListDrag(wxCommandEvent& event);

////@end CBMImager event handler declarations

////@begin CBMImager member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CBMImager member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CBMImager member variables
	wxMenu* m_FileMenu;
	wxMenu* m_extrasMenu;
	wxMenu* m_importMenu;
	CODListBox* m_FileList;
	wxStatusBar* m_StatusBar;

	wxBoxSizer *m_sizerMain;
	wxSplitterWindow *m_splitter;
	wxBoxSizer *m_upperBoxSizer;
	wxBoxSizer *m_lowerBoxSizer;
	wxPanel *m_upperPanel;
	wxPanel *m_lowerPanel;
	wxListCtrl *m_actionList;
	wxTextCtrl *m_messageLog;
	wxLogTextCtrl *m_logTextCtrl;
////@end CBMImager member variables

	void OpenImage(wxString& fileName);
	void ReadCbmDirectory();
	void AddFile(wxString& filename);
	void ExtractFile(CCbmDirectoryEntry *entry, wxString& fileName, bool showError = true, bool writeP00 = false);
	CbmImageType GetCurrentImageType();
	bool IsDragSource();
	void SetItemUnderCursor(int index);

private:
	wxBitmap image;
	CCbmImageBase *cbmImage;
	CCbmDirectory *cbmDir;
	BAMStack bamStack;				// Stores the BAM's of Directorys
	bool isDragSource;
	wxArrayString usedTempFiles;
	int itemUnderCursor;

	wxString strApplicationPath;			// application path
	wxFileName tConfigFileName;			// config filename
	wxFileConfig *ptConfigFile;			// config file object

	wxString GetApplicationPath(void);
	void ShowVersionInfo(void);

	void readConfig(void);
	void writeConfig(void);
};

/*!
 * CBMImager class declaration
 */


#endif
    // _CBMIMAGER_H_
