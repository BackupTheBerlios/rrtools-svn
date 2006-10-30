#pragma once
#include <wx/vlbox.h>

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
