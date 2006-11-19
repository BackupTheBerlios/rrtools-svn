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

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "CbmImagerApp.h"
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

#include "cbmimagerapp.h"

////@begin XPM images
////@end XPM images

/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( CbmImagerApp )
////@end implement app

/*!
 * CbmImagerApp type definition
 */

IMPLEMENT_CLASS( CbmImagerApp, wxApp )

/*!
 * CbmImagerApp event table definition
 */

BEGIN_EVENT_TABLE( CbmImagerApp, wxApp )

////@begin CbmImagerApp event table entries
////@end CbmImagerApp event table entries

END_EVENT_TABLE()

/*!
 * Constructor for CbmImagerApp
 */

CbmImagerApp::CbmImagerApp()
{
    Init();
}

/*!
 * Member initialisation 
 */

void CbmImagerApp::Init()
{
////@begin CbmImagerApp member initialisation
////@end CbmImagerApp member initialisation
/*!
 * Initialisation for CbmImagerApp
 */
}

bool CbmImagerApp::OnInit()
{    
////@begin CbmImagerApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	CBMImager* mainWindow = new CBMImager( NULL, ID_CBMIMAGER );
	mainWindow->Show(true);
////@end CbmImagerApp initialisation

    return true;
}

/*!
 * Cleanup for CbmImagerApp
 */
int CbmImagerApp::OnExit()
{    
////@begin CbmImagerApp cleanup
	return wxApp::OnExit();
////@end CbmImagerApp cleanup
}

