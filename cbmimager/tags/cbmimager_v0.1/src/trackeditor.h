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
#pragma interface ""
#endif

/*!
 * Includes
 */

////@begin includes
#include "hexcontrol.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define ID_LISTBOX1 10001
#define ID_BUTTON1 10002
#define ID_BUTTON2 10003
#define ID_BUTTON3 10004
#define ID_BUTTON4 10005
#define ID_BUTTON5 10006
#define SYMBOL_CTRACKEDITOR_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CTRACKEDITOR_TITLE _("Track Editor")
#define SYMBOL_CTRACKEDITOR_IDNAME ID_DIALOG
#define SYMBOL_CTRACKEDITOR_SIZE wxSize(400, 300)
#define SYMBOL_CTRACKEDITOR_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * CTrackEditor class declaration
 */

class CTrackEditor: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CTrackEditor )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CTrackEditor( );
    CTrackEditor( wxWindow* parent, wxWindowID id = SYMBOL_CTRACKEDITOR_IDNAME, const wxString& caption = SYMBOL_CTRACKEDITOR_TITLE, const wxPoint& pos = SYMBOL_CTRACKEDITOR_POSITION, const wxSize& size = SYMBOL_CTRACKEDITOR_SIZE, long style = SYMBOL_CTRACKEDITOR_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CTRACKEDITOR_IDNAME, const wxString& caption = SYMBOL_CTRACKEDITOR_TITLE, const wxPoint& pos = SYMBOL_CTRACKEDITOR_POSITION, const wxSize& size = SYMBOL_CTRACKEDITOR_SIZE, long style = SYMBOL_CTRACKEDITOR_STYLE );

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CTrackEditor event handler declarations
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnButtonPrevLogical( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
    void OnButtonPrevLinked( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
    void OnButtonNextLogical( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4
    void OnButtonNextLinked( wxCommandEvent& event );

	void OnButtonApply( wxCommandEvent& event );
	void OnClose( wxCloseEvent& event);

////@end CTrackEditor event handler declarations

////@begin CTrackEditor member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CTrackEditor member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();


	void SetCbmImage(CCbmImageBase *image);
	void SetCbmCharset(byte* buffer, int nLength);
	void SetStartInfo(int track, int sector);


	wxButton *btnPrevLogical;
	wxButton *btnPrevLinked;
	wxButton *btnNextLogical;
	wxButton *btnNextLinked;

////@begin CTrackEditor member variables
    CHexControl* m_hexList;
////@end CTrackEditor member variables

private:
	CCbmImageBase *cbmImage;
	CCbmSector *currentSector;
	int m_track, m_sector;
	int m_prevTrack, m_prevSector;		// previous linked sector

	void DisplaySector();
	void EnableButtons();
};

