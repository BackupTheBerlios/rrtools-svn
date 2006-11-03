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

#include "odlistbox.h"


#define ID_HEXCONTROL	10010


class CHexControl :
	public CODListBox
{
public:
	CHexControl(wxWindow* parent, wxWindowID id = ID_HEXCONTROL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
		long style = 0, const wxString& name = _T("HexControl"));

	virtual void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const;
	virtual void Clear();

	void SetData(byte *data, int nLength);

	virtual void OnMouseEvent(wxMouseEvent& event);
	virtual void OnKeyDown(wxKeyEvent& event);

protected:
	byte *m_data;					// pointer to hex-data
	int m_dataLength;				// Length of data
	int m_selRow;
	int m_selCol;
	int m_colHex, m_colAscii;

	void UpdateColPositions();

	DECLARE_EVENT_TABLE()

};
