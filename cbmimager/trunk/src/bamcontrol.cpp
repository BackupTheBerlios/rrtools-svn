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

#include "bamcontrol.h"
#include "bameditor.h"


// Custom selection event
DEFINE_EVENT_TYPE(wxEVT_BAMCONTROL_SELECTION_EVENT)

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_BAMCONTROL_SELECTION_EVENT, wxID_ANY)
END_DECLARE_EVENT_TYPES()




BEGIN_EVENT_TABLE(CBamControl, wxVListBox)
	EVT_MOUSE_EVENTS(CBamControl::OnMouseEvent)
	EVT_KEY_DOWN(CBamControl::OnKeyDown)
END_EVENT_TABLE()



CBamControl::CBamControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
					   long style, const wxString& name) : CODListBox(parent, id, pos, size, style, name)
{
	cbmImage = NULL;
	m_selRow = -1;
	m_selCol = -1;
	m_selTrack = 0;
	m_selSector = 0;
	SetItemCount(0);
}


CBamControl::~CBamControl(void)
{
}


void CBamControl::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const
{
	wxMemoryDC tempDC;
	int track, sector;

	((CBamControl*)this)->MapSector(n << 4, &track, &sector);

	wxString output;
	wxString selected;
	for (int i = 0; i < 16; i++)
	{
		if (track > cbmImage->GetNumTracks())
			break;

		if (cbmImage->IsSectorFree(track, sector))
			output.Append(0x57);
		else
			output.Append(0x51);
		if (m_selectedSectors.Index((track << 16) + sector) == wxNOT_FOUND)		// is the sector selected ?
			selected.Append('0');
		else
			selected.Append('1');
		if ((sector + 1) < CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType()))
			sector++;
		else
		{
			track++;
			sector = 0;
		}
	}

	int len = output.Len();
	for (int i = 0; i < len; i++)
	{
		byte pi = output.GetChar(i);
		if ((m_selRow == (int)n && m_selCol == i) || selected.GetChar(i) == '1')
			tempDC.SelectObject(selBitmap);
		else
			tempDC.SelectObject(stdBitmap);
		dc.Blit(i * charWidth + rect.x, rect.y, charWidth, charHeigth, &tempDC, pi<<3, 0);
	}
}


void CBamControl::Clear()
{
	wxVListBox::Clear();
}


void CBamControl::SetImage(CCbmImageBase *image)
{
	int nBits = 0;
	int numTracks;

	cbmImage = image;
	
	numTracks = cbmImage->GetNumTracks();
	for (int i = 1; i <= numTracks; i++)
	{
		nBits += CCbmImageBase::GetSectorCount(i, cbmImage->GetImageType());
	}
	SetItemCount(nBits / 16);
	if ((nBits % 16) > 0)
		SetItemCount(nBits / 16 + 1);
}


void CBamControl::OnMouseEvent(wxMouseEvent& event)
{
	int track, sector;

	if (event.LeftIsDown())
	{
		size_t first = GetFirstVisibleLine();	// First visible row
		int sel = event.m_y / 8;				// selected row (relative to first visible)
		SetSelection(sel);
		m_selRow = sel + first;					// absolute row
		m_selCol = event.m_x / 8;
		if (m_selCol >= 16)
			m_selCol = -1;						// Reset, when outside the editable region
		Refresh();
		ScrollToLine(first);

		MapSector((m_selRow << 4) + m_selCol, &track, &sector);

		// check for valid selection
		if (track <= cbmImage->GetNumTracks() && sector < CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType()))
		{
			if (m_selCol != -1)
			{
				m_selTrack = track;
				m_selSector = sector;
				wxCommandEvent eventCBMSel(wxEVT_BAMCONTROL_SELECTION_EVENT);
				wxPostEvent( this, eventCBMSel);		// Send Sector-Selected Event
			}
			else
				m_selTrack = m_selSector = -1;
		}
		else
			m_selTrack = m_selSector = -1;

		// Signal an invalid selection
		if (m_selTrack == -1 && m_selSector == -1)
		{
			wxCommandEvent eventCBMSel(wxEVT_BAMCONTROL_SELECTION_EVENT);
			wxPostEvent( this, eventCBMSel);		// Send Sector-Selected Event
		}
	}
	event.Skip();
}


void CBamControl::OnKeyDown(wxKeyEvent& event)
{
	if (event.m_keyCode == 32)				// Space ?
	{
		if (m_selTrack > 0 && m_selSector >= 0)
		{
			if (cbmImage->IsSectorFree(m_selTrack, m_selSector))		// Toggle Sector allocation
				cbmImage->AllocateSector(m_selTrack, m_selSector);
			else
				cbmImage->FreeSector(m_selTrack, m_selSector);
			Refresh();
		}
	}
	else if (event.m_keyCode >= 316 && event.m_keyCode <= 319)		// Cursor Keys ?
	{
		if (event.m_keyCode == 316 && m_selCol > 0)					// Left
		{
			m_selCol --;
		}
		else if (event.m_keyCode == 318 && m_selCol < 15)			// Right
		{
			m_selCol++;
		}
		else if (event.m_keyCode == 317 && m_selRow > 0)			// Up
		{
			m_selRow--;
			if (m_selRow < (int)GetFirstVisibleLine())
				ScrollToLine(m_selRow);
		}
		else if (event.m_keyCode == 319 && (int)GetItemCount() > (m_selRow + 1))	// Down
		{
			m_selRow++;
			if ((m_selRow + 1) >= (int)GetVisibleEnd())
				ScrollToLine(GetFirstVisibleLine() + 1);
		}
		MapSector((m_selRow << 4) + m_selCol, &m_selTrack, &m_selSector);			// Update Track/Sector

		RefreshLine(GetSelection());
		RefreshLine(GetSelection() + 1);
		RefreshLine(GetSelection() - 1);		// don't refresh the whole list !
		SetSelection(m_selRow);
		wxCommandEvent eventCBMSel(wxEVT_BAMCONTROL_SELECTION_EVENT);
		wxPostEvent( this, eventCBMSel);		// Send Sector-Selected Event
	}
	event.Skip();
}


void CBamControl::MapSector(int absSector, int *destTrack, int *destSector)
{
	int track = 1;

	while (absSector > 16)	// we're showing 16 Sectors in a row
	{
		if (absSector < CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType()))
			break;
		absSector -= CCbmImageBase::GetSectorCount(track, cbmImage->GetImageType());
		track++;
	}
	*destTrack = track;
	*destSector = absSector;
}


void CBamControl::AddFileSector(unsigned long trackSector)
{
	m_selectedSectors.Add(trackSector);
	m_selCol = -1;
	m_selRow = -1;			// Reset the manual selection
}

void CBamControl::ClearFileSectors()
{
	m_selectedSectors.Clear();
}


void CBamControl::GetCbmSelection(int *track, int *sector)
{
	*track = m_selTrack;
	*sector = m_selSector;
}
