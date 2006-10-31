#pragma once

#include "wx/wx.h"

#include "odlistbox.h"
#include "Logic/imagebase.h"
#include "Logic/cbmdirectory.h"
#include "Logic/cbmdirectoryentry.h"


#define ID_BAMCONTROL 10011

#ifdef __UNIX__
typedef unsigned long DWORD;
#endif


// Define Event for Sector-Selection
DECLARE_EXPORTED_EVENT_TYPE(, wxEVT_BAMCONTROL_SELECTION_EVENT, 0)

#define EVT_BAMCONTROL_SELECTION_EVENT(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
		wxEVT_BAMCONTROL_SELECTION_EVENT, id, wxID_ANY, \
		(wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
		(wxObject *) NULL \
	),



WX_DEFINE_ARRAY(DWORD, FileSectors);


class CBamControl :
	public CODListBox
{
public:
	virtual ~CBamControl(void);

	CBamControl(wxWindow* parent, wxWindowID id = ID_BAMCONTROL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(160, 200), 
		long style = 0, const wxString& name = _T("BamControl"));

	virtual void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const;
	virtual void Clear();

	virtual void OnMouseEvent(wxMouseEvent& event);
	virtual void OnKeyDown(wxKeyEvent& event);


	void SetImage(CCbmImageBase *image);
	// Maps an absolute SectorNumber to the "real" track and sector
	void MapSector(int absSector, int *track, int *sector);
	void AddFileSector(DWORD trackSector);
	void ClearFileSectors();
	void GetCbmSelection(int *track, int *sector);


protected:
	CCbmImageBase *cbmImage;
	FileSectors m_selectedSectors;
	int m_selRow;
	int m_selCol;
	int m_selTrack, m_selSector;		// current Selection

	DECLARE_EVENT_TABLE()

};
