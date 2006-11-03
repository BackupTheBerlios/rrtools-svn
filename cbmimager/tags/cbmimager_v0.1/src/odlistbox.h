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

#pragma once

#include "wx/vlbox.h"
#include "wx/dynarray.h"
#include "Logic/cbmdirectoryentry.h"


#define ID_ODLISTBOX		10010


DECLARE_EVENT_TYPE(wxEVT_MY_DRAG_EVENT, -1)



WX_DEFINE_ARRAY(wxString*, ItemArray);
WX_DEFINE_ARRAY(CCbmDirectoryEntry*, EntryArray);



class CODListBox :
	public wxVListBox
{
public:
	CODListBox(wxWindow* parent, wxWindowID id = ID_ODLISTBOX, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
		long style = 0, const wxString& name = _T("ODListBox"));

	virtual ~CODListBox(void);

	virtual wxCoord OnMeasureItem(size_t n)const;
	void OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n)const;
	virtual void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const;
	virtual void Clear();

	bool SetCBMCharset(byte *buffer, int nLength);
	bool SetCBMCharset(char *fileName);

	void AddItem(wxString *text, CCbmDirectoryEntry *dirEntry);
	void AddItem(wxString text, CCbmDirectoryEntry *dirEntry);
	wxString *GetItem(int index) const;
	CCbmDirectoryEntry *GetEntry(int index) const;

	void OnItemSelected(wxCommandEvent& event);

	virtual void OnMouseEvent(wxMouseEvent& event);

private:
	void createMirrorMap(void);
	byte abMirrorTab[0x0100];

protected:
	wxBitmap stdBitmap;			// Source of BitmapCharset (items are displayed in normal state)
	wxBitmap selBitmap;			// items are selected in selected State
	int charsPerRow;				// Number of chars per Row
	int charHeigth;					// Height of each char
	int charWidth;					// Height of each char
//	wxPoint *charPositions[256];	// Position of each char in the Bitmap
	ItemArray items;				// Stores the Items of the ListBox
	EntryArray entries;				// Stores the DirectoryEntries for each item
	int dragX, dragY;				// to slow down the start of the drag-process

	wxBrush tBrushStdBackground;
	wxBrush tBrushStdForeground;
	wxBrush tBrushSelBackground;
	wxBrush tBrushSelForeground;

	DECLARE_EVENT_TABLE()
};
