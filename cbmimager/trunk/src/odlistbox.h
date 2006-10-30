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
	void BuildSelectionBitmap();

	void AddItem(wxString *text, CCbmDirectoryEntry *dirEntry);
	void AddItem(wxString text, CCbmDirectoryEntry *dirEntry);
	wxString *GetItem(int index);
	CCbmDirectoryEntry *GetEntry(int index);

	void OnItemSelected(wxCommandEvent& event);

	virtual void OnMouseEvent(wxMouseEvent& event);
    
protected:
	wxBitmap *stdBitmap;			// Source of BitmapCharset (items are displayed in normal state)
	wxBitmap *selBitmap;			// items are selected in selected State
	int charsPerRow;				// Number of chars per Row
	int charHeigth;					// Height of each char
	int charWidth;					// Height of each char
	wxPoint *charPositions[256];	// Position of each char in the Bitmap
	ItemArray items;				// Stores the Items of the ListBox
	EntryArray entries;				// Stores the DirectoryEntries for each item
	int dragX, dragY;				// to slow down the start of the drag-process

	DECLARE_EVENT_TABLE()
};
