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

// Generated by DialogBlocks (unregistered), 16/10/2006 20:30:06

#ifndef _SELECTIMAGE_H_
#define _SELECTIMAGE_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "selectimage.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/dirctrl.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxGenericDirCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_SELECTIMAGE 10009
#define ID_GENERICDIRCTRL 10010
#define SYMBOL_SELECTIMAGE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_SELECTIMAGE_TITLE _("Select Image")
#define SYMBOL_SELECTIMAGE_IDNAME ID_SELECTIMAGE
#define SYMBOL_SELECTIMAGE_SIZE wxDefaultSize
#define SYMBOL_SELECTIMAGE_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * SelectImage class declaration
 */

class SelectImage: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SelectImage )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SelectImage( );
    SelectImage( wxWindow* parent, wxWindowID id = SYMBOL_SELECTIMAGE_IDNAME, const wxString& caption = SYMBOL_SELECTIMAGE_TITLE, const wxPoint& pos = SYMBOL_SELECTIMAGE_POSITION, const wxSize& size = SYMBOL_SELECTIMAGE_SIZE, long style = SYMBOL_SELECTIMAGE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SELECTIMAGE_IDNAME, const wxString& caption = SYMBOL_SELECTIMAGE_TITLE, const wxPoint& pos = SYMBOL_SELECTIMAGE_POSITION, const wxSize& size = SYMBOL_SELECTIMAGE_SIZE, long style = SYMBOL_SELECTIMAGE_STYLE );

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SelectImage event handler declarations

////@end SelectImage event handler declarations

////@begin SelectImage member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SelectImage member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SelectImage member variables
    wxGenericDirCtrl* m_FileSelector;
////@end SelectImage member variables
};

#endif
    // _SELECTIMAGE_H_
