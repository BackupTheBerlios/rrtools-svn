/////////////////////////////////////////////////////////////////////////////
// Name:        CbmImagerApp.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/10/2006 19:05:43
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

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
