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

#ifndef _CBMIMAGERAPP_H_
#define _CBMIMAGERAPP_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "CbmImagerApp.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "cbmimager.h"
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
////@end control identifiers

/*!
 * CbmImagerApp class declaration
 */

class CbmImagerApp: public wxApp
{
    DECLARE_CLASS( CbmImagerApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    CbmImagerApp();

    /// Initialises member variables
    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin CbmImagerApp event handler declarations

////@end CbmImagerApp event handler declarations

////@begin CbmImagerApp member function declarations

////@end CbmImagerApp member function declarations

////@begin CbmImagerApp member variables
////@end CbmImagerApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(CbmImagerApp)
////@end declare app

#endif
    // _CBMIMAGERAPP_H_
