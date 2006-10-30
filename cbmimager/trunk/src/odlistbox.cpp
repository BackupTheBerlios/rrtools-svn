#include "odlistbox.h"

#include "cbmimager_id.h"

#include "wx/wx.h"
#include "wx/rawbmp.h"
#include "wx/ffile.h"



BEGIN_EVENT_TABLE(CODListBox, wxVListBox)
	EVT_MOUSE_EVENTS(CODListBox::OnMouseEvent)
	EVT_LISTBOX(ID_ODLISTBOX, CODListBox::OnItemSelected)
END_EVENT_TABLE()


CODListBox::CODListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
					   long style, const wxString& name) : wxVListBox(parent, id, pos, size, style, name)
{
	stdBitmap = NULL;
	selBitmap = NULL;
	memset(charPositions, 0, sizeof(charPositions));
	SetItemCount(0);
	dragX = -1;
	dragY = -1;
}

CODListBox::~CODListBox(void)
{
	for (int i = 0; i < 256; i++)
		if (charPositions[i] != NULL)
			delete charPositions[i];
	Clear();
	delete selBitmap;
	delete stdBitmap;
}


void CODListBox::Clear()
{
	wxVListBox::Clear();
	for (int i = 0; i < (int)items.Count(); i++)
		delete items[i];
	items.Clear();
	entries.Clear();
}

wxCoord CODListBox::OnMeasureItem(size_t n)const
{
	wxUnusedVar(n);
	return (wxCoord) charHeigth;
}


void CODListBox::OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n)const
{
	wxUnusedVar(n);
	wxUnusedVar(dc);
	wxUnusedVar(rect);
}


void CODListBox::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n)const
{
	wxMemoryDC tempDC;

	if (n >= items.Count())
		return;

	if (this->IsSelected(n))
		tempDC.SelectObject(*selBitmap);
	else
		tempDC.SelectObject(*stdBitmap);
	wxString *text = ((CODListBox*)this)->GetItem(n);
	int len = text->Len();
	for (int i = 0; i < len; i++)
	{
		byte pi = text->GetChar(i);
		if (pi >= 64 && pi < 128)
			pi -= 64;
		if (pi >= 192)			// TODO: ARGH !! Can we get this easier ??
			pi -= 64;
		if (pi >= 64)
			pi -= 64;
		dc.Blit(i * charWidth + rect.x, rect.y, charWidth, charHeigth, &tempDC, charPositions[pi]->x, charPositions[pi]->y);
	}
}


bool CODListBox::SetCBMCharset(byte *buffer, int nLength)
{
	int i, x, y, t;
	byte currentValue;
	byte color;
	byte currentChar;
	byte bit;
	int nStart = nLength % 2048;

	// when omitting the last parameter (bit-depth), the program crashes under Win ( at "PixelData data(*stdBitmap)" )
	stdBitmap = new wxBitmap(8 * 32, 8 * 8, 24);		// 32 Chars per Row, 8 Rows height
	wxMemoryDC memDC;
	memDC.SelectObject(*stdBitmap);
	memDC.Clear();
	memDC.SelectObject(wxNullBitmap);

	typedef wxPixelData<wxBitmap, wxNativePixelFormat> PixelData;
	PixelData data(*stdBitmap);
	if (!data)
		return false;
	PixelData::Iterator p(data);

	currentChar = 0;
	for (i = nStart; i < nStart + 2048; i++)
	{
		x = (i - nStart) & 0xff;
		y = ((i - nStart) >> 8) * 8;
		charPositions[currentChar++] = new wxPoint(x, y);
		for (t = 0; t < 8; t++)
		{
			currentValue = buffer[i + t];
			for (bit = 128; bit > 0; bit >>= 1)
			{
				if ((currentValue & bit) == bit)
					color = 0;
				else
					color = 255;
				p.MoveTo(data, x, y);
				p.Red() = color;
				p.Green() = color;
				p.Blue() = color;
				x++;
			}
			y++;
			x -= 8;
		}
		i += 7;
	}

	charWidth = 8;
	charHeigth = 8;
	BuildSelectionBitmap();
	return true;
}


bool CODListBox::SetCBMCharset(char *fileName)
{
	byte *buffer;
	wxFFile f(wxString::FromAscii(fileName), wxT("rb"));
	if (f.IsOpened())
	{
		f.Seek(0, wxFromEnd);
		long length = f.Tell();
		buffer = new byte[length];
		f.Seek(0);
		f.Read(buffer, length);
		f.Close();
		SetCBMCharset(buffer, length);
		delete buffer;
		return true;
	}
	return false;
}


void CODListBox::BuildSelectionBitmap()
{
	int x, y;


	this->selBitmap = new wxBitmap(stdBitmap->GetWidth(), stdBitmap->GetHeight(), stdBitmap->GetDepth());
	// Make a copy of the Bitmap
	wxMemoryDC oldDC;
	wxMemoryDC newDC;
	oldDC.SelectObject(*stdBitmap);		// Select original Bitmap
	newDC.SelectObject(*selBitmap);		// Select empty Bitmap
	newDC.Blit(0, 0, stdBitmap->GetWidth(), stdBitmap->GetHeight(), &oldDC, 0, 0);	// Paint original over empty
	newDC.SelectObject(wxNullBitmap);
	oldDC.SelectObject(wxNullBitmap);
	
	// Set the white Colors of selBitmap to blue (selected Items will be painted with this bitmap)
	typedef wxPixelData<wxBitmap, wxNativePixelFormat> PixelData;
	PixelData data(*selBitmap);
	if (!data)
		return;

	int height = data.GetHeight();
	int width = data.GetWidth();
	PixelData::Iterator p(data);
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			p.MoveTo(data, x, y);
			if (p.Red() == 255 && p.Green() == 255 && p.Blue() == 255)
			{
				p.Red() = 64;
				p.Green() = 136;
			}
		}
	}
}


void CODListBox::AddItem(wxString *text, CCbmDirectoryEntry *dirEntry)
{
	items.Add(new wxString(*text));		// Clone the string
	entries.Add(dirEntry);
	SetItemCount(items.Count());
}
void CODListBox::AddItem(wxString text, CCbmDirectoryEntry *dirEntry)
{
	items.Add(new wxString(text));		// Clone the string
	entries.Add(dirEntry);
	SetItemCount(items.Count());
}


wxString *CODListBox::GetItem(int index)
{
	return (wxString*)items[index];
}

CCbmDirectoryEntry* CODListBox::GetEntry(int index)
{
	return entries[index];
}


//
// Custom Event Handlers
// 


void CODListBox::OnMouseEvent(wxMouseEvent& event)
{
	if (event.Dragging())
	{
		if (dragX == -1)
		{
			dragX = event.m_x;
			dragY = event.m_y;
		}
		// only start dragging, if we have moved the mouse some pixels
		if (abs(dragX - event.m_x) > 4 || abs(dragY - event.m_y) > 4)
		{
			wxCommandEvent eventODLDrag(wxEVT_ODLISTBOX_DRAG_EVENT);
			wxPostEvent( this, eventODLDrag);
			dragX = -1;
			dragY = -1;
		}
	}
	else
	{
		dragX = -1;
		dragY = -1;
		event.Skip(true);
	}
}


void CODListBox::OnItemSelected(wxCommandEvent& event)
{
	wxCommandEvent eventODLselect(wxEVT_ODLISTBOX_SELECTION_EVENT);
	wxPostEvent( this, eventODLselect);
	event.Skip(true);
}
