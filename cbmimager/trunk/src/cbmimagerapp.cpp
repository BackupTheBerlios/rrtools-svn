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

#include "cbmimager_version.h"
#include "cbmimagerapp.h"


// some necessary wx features
//#if !wxUSE_ZIPSTREAM
//	#error "This tool requires zipstream support!"
//#endif

//#if !wxUSE_ZLIB
//	#error "This tool requires zlib support!"
//#endif


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
	CBMImager *mainWindow;


	wxInitAllImageHandlers();
//	wxFileSystem::AddHandler(new wxZipFSHandler);

	// set application and vendor name, this is needed
	// for the config file (unix) or registry keys (win)
	SetVendorName(wxT("TheDreams"));
	SetAppName(wxString::FromAscii(CBMIMAGER_APPLICATION_NAME));

	// create the main window
	mainWindow = new CBMImager(NULL, ID_CBMIMAGER);

	// show the main window
	mainWindow->Show(true);
	SetTopWindow(mainWindow);

	return true;
}

/*!
 * Cleanup for CbmImagerApp
 */
int CbmImagerApp::OnExit()
{
	wxConfigBase *pConfig;


	pConfig = wxConfigBase::Set((wxConfigBase *) NULL);
	if( pConfig!=NULL ) {
		delete pConfig;
	}

	return wxApp::OnExit();
}

