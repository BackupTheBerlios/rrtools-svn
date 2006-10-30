/////////////////////////////////////////////////////////////////////////////
// Name:        
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/10/2006 19:17:51
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _APP_RESOURCES_H_
#define _APP_RESOURCES_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface ""
#endif

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

class AppResources
{
public:
    AppResources() {}

/*!
 * Resource functions
 */

////@begin AppResources resource functions
    /// Menu creation function for ID_MENU
    static wxMenu* CreateMenuMenu();

    /// Retrieves bitmap resources
    static wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    static wxIcon GetIconResource( const wxString& name );
////@end AppResources resource functions

};

#endif
    // _APP_RESOURCES_H_
