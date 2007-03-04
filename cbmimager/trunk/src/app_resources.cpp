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

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation ""
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

#include "app_resources.h"

////@begin XPM images
////@end XPM images

/*!
 * Resource functions
 */

////@begin AppResources resource functions
/*!
 * Menu creation function for ID_MENU
 */

wxMenu* AppResources::CreateMenuMenu()
{
    wxMenu* itemMenu1 = new wxMenu;
    return itemMenu1;
}

////@end AppResources resource functions

/*!
 * Get bitmap resources
 */

wxBitmap AppResources::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AppResources bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AppResources bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon AppResources::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    // Icon retrieval
////@begin AppResources icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AppResources icon retrieval
}
