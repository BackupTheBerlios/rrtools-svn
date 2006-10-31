#include "hexcontrol.h"

#include "wx/wx.h"
#include "wx/rawbmp.h"
#include "wx/ffile.h"



BEGIN_EVENT_TABLE(CHexControl, wxVListBox)
	EVT_MOUSE_EVENTS(CHexControl::OnMouseEvent)
	EVT_KEY_DOWN(CHexControl::OnKeyDown)
END_EVENT_TABLE()


CHexControl::CHexControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
					   long style, const wxString& name) : CODListBox(parent, id, pos, size, style, name)
{
	m_data = NULL;
	m_dataLength = 0;
	m_selRow = -1;
	m_selCol = -1;
	SetItemCount(0);
}


void CHexControl::SetData(byte *data, int nLength)
{
	m_data = data;
	m_dataLength = nLength;
	SetItemCount(nLength / 8);
	if (nLength % 8 > 0)
		SetItemCount(nLength / 8 + 1);
}


void CHexControl::Clear()
{
	wxVListBox::Clear();
}


void CHexControl::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const
{
	wxMemoryDC tempDC;
	int startIndex;
	wxString output;
	wxString bTemp;
	int i;
	int len;
	byte pi;


	if (m_dataLength == 0)
	{
		return;
	}

	((CHexControl*)this)->UpdateColPositions();

	startIndex = n * 8;
	output.Printf(wxT("%04X  "), startIndex);
	for (i = 0; i < 8; i++)
	{
		if (startIndex + i >= m_dataLength)
		{
			break;
		}
		bTemp.Printf(wxT("%02X "), m_data[startIndex + i]);
		output.Append(bTemp);
	}
	while (output.Len() < 31)
	{
		output.Append(_T(" "));
	}

	for (i = 0; i < 8; i++)
	{
		if (startIndex + i >= m_dataLength)
		{
			break;
		}
		output.Append(m_data[startIndex + i]);
	}

	len = output.Len();
	for (i = 0; i < len; i++)
	{
		pi = output.GetChar(i);
		if (pi >= 64 && pi < 128)
			pi -= 64;
		if (pi >= 192)			// TODO: ARGH !! Can we get this easier ??
			pi -= 64;
		if (pi >= 64)
			pi -= 64;
		if (m_selRow == (int)n && (m_colHex == i || m_colAscii == i))
		{
			tempDC.SelectObject(selBitmap);
		}
		else
		{
			tempDC.SelectObject(stdBitmap);
		}
		dc.Blit(i * charWidth + rect.x, rect.y, charWidth, charHeigth, &tempDC, pi<<3, 0);
	}
}


void CHexControl::OnMouseEvent(wxMouseEvent& event)
{
	char forbiddenCols[] = 
	{
		8,11,14,17,20,23,26,29,30
	};

	if (event.LeftIsDown())
	{
		size_t first = GetFirstVisibleLine();	// First visible row
		int sel = event.m_y / 8;				// selected row (relative to first visible)
		SetSelection(sel);
		m_selRow = sel + first;					// absolute row
		m_selCol = event.m_x / 8;
		if (m_selCol < 6 || m_selCol > 38)
			m_selCol = -1;						// Reset, when outside the editable region
		else
		{
			for (int i = 0; i < sizeof(forbiddenCols); i++)
			{
				if (m_selCol == forbiddenCols[i])
				{
					m_selCol = -1;					// invalid position inside the hex-view
					break;
				}
			}
			if (m_selCol != -1)
			{
				int offset = m_selRow * 8;			// Start of row in m_data
				int b = (m_selCol - 6) / 3;			// byte offset for the row (4 cols for address + 2 spaces, each byte consist of 2 chars + 1 space)
				if (m_selCol > 30)					// in ASCII-Part
					b = m_selCol - 31;				// fix offset
				if (offset + b >= m_dataLength)		// end of data reached
					m_selCol = -1;
			}
		}
		Refresh();
		ScrollToLine(first);
	}
	event.Skip();
}


void CHexControl::OnKeyDown(wxKeyEvent& event)
{
	byte value;
	int offset = m_selRow * 8;					// Start of row in m_data
	int b = (m_selCol - 6) / 3;					// byte offset for the row (4 cols for address + 2 spaces, each byte consist of 2 chars + 1 space)
	bool high = (m_selCol - 6) % 3 == 0;		// is the high-nibble selected ?
	byte target = m_data[offset + b];			// read byte from data-buffer

	if (event.m_keyCode >= 326 && event.m_keyCode <= 335)				// Numberblock ?
		event.m_keyCode -= 278;											// Map to normal Numbers

	if (m_selCol < 29 && m_selCol >= 6)									// in hex-view ?
	{
		if (event.m_keyCode >= 48 && event.m_keyCode <= 57)				// Numeric char ?
		{
			value = event.m_keyCode - 48;
		}
		else if (event.m_keyCode >= 65 && event.m_keyCode <= 70)		// A-F ?
		{
			value = event.m_keyCode - 55;
		}
		else if (event.m_keyCode >= 316 && event.m_keyCode <= 319)		// Cursor Keys ?
		{
			if (event.m_keyCode == 316 && m_selCol > 6)					// Left
			{
				if (high)
					m_selCol -= 2;
				else
					m_selCol--;
			}
			else if (event.m_keyCode == 318 && m_selCol < 28)			// Right
			{
				if (!high && offset + b + 1 < m_dataLength)
					m_selCol += 2;
				else if (high && offset + b < m_dataLength)
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
			RefreshLine(GetSelection());
			RefreshLine(GetSelection() + 1);
			RefreshLine(GetSelection() - 1);		// don't refresh the whole list !
			SetSelection(m_selRow);
			return;
		}
		else							// invalid char encountered
		{
			event.Skip();
			return;
		}
		if (high)						// high-nibble selected ?
		{
			target &= 0x0f;				// clear high-byte
			value <<= 4;				// shift value to high-nibble
			m_selCol++;					// move to next byte
		}
		else							// low-nible was selected
		{
			target &= 0xf0;				// clear low-nibble
			if (m_selCol == 28 && (int)GetItemCount() > (m_selRow + 1))		// End of Line but not last line ?
			{
				m_selCol = 4;			// move to start of line
				m_selRow++;				// next line
			}
			if (m_selCol < 28 && offset + b + 1 < m_dataLength)					// not on the rightmost position ?
				m_selCol += 2;			// move to next byte
		}
		target |= value;				// set value
		m_data[offset + b] = target;	// and store it
	}
	else if (m_selCol > 30)												// we're in the ASCII-Part of the hexdump
	{
		b = m_selCol - 31;												// fix offset
		if (event.m_keyCode >= 32 && event.m_keyCode < 127)
		{
			target = event.m_keyCode;
			if (event.ShiftDown())
			{
				if (event.m_keyCode >= 48 && event.m_keyCode <= 57)			// Shifted Numbers needs special attention
					target -= 16;
				else
					target += 64;
			}
			m_data[offset + b] = target;
			if (m_selCol == 38 && (int)GetItemCount() > (m_selRow + 1))		// End of Line but not last line ?
			{
				m_selCol = 30;			// move to start of line
				m_selRow++;				// next line
			}
			if (m_selCol < 38)
			{
				if (offset + b + 1 < m_dataLength)
					m_selCol++;
			}
		}
		else if (event.m_keyCode >= 316 && event.m_keyCode <= 319)		// Cursor Keys ?
		{
			if (event.m_keyCode == 316 && m_selCol > 31)				// Left
			{
				m_selCol--;
			}
			else if (event.m_keyCode == 318 && m_selCol < 38)			// Right
			{
				if (offset + b + 1 < m_dataLength)
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
			RefreshLine(GetSelection());
			RefreshLine(GetSelection() + 1);
			RefreshLine(GetSelection() - 1);		// don't refresh the whole list !
			SetSelection(m_selRow);
			return;
		}
		else							// invalid char encountered
		{
			event.Skip();
			return;
		}
	}

	Refresh();
}


// This function synchronizes the Cursor-Position in Hex- and ASCII-Mode
void CHexControl::UpdateColPositions()
{
	if (m_selCol == -1)
	{
		m_colHex = -1;
		m_colAscii = -1;
		return;
	}
	if (m_selCol > 30)			// in Ascii Part
	{
		m_colHex = m_selCol - 31;
		m_colHex = m_colHex * 3 + 6;
		m_colAscii = m_selCol;
	}
	else						// in Hex Part
	{
		m_colHex = m_selCol;
		m_colAscii = (m_selCol - 6) / 3 + 31;
	}
}
