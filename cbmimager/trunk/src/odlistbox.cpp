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
	SetItemCount(0);
	dragX = -1;
	dragY = -1;

	createMirrorMap();

	// set the standard colors
	tBrushStdBackground.SetColour(*wxWHITE);
	tBrushStdForeground.SetColour(*wxBLACK);
	tBrushSelBackground.SetColour(*wxBLUE);
	tBrushSelForeground.SetColour(*wxWHITE);
}


void CODListBox::createMirrorMap(void)
{
	int iByteCnt;
	int iBitCnt;
	byte bShift;
	byte bRes = 0;


	iByteCnt = 0;
	do
	{
		bShift = (byte)iByteCnt;
		iBitCnt = 0;
		do
		{
			bRes <<= 1;
			bRes |= bShift&1;
			bShift >>= 1;
			abMirrorTab[iByteCnt] = bRes;
		} while( ++iBitCnt<8 );
	} while( ++iByteCnt<256 );
}


CODListBox::~CODListBox(void)
{
	for (int i = 0; i < 256; i++)
//		if (charPositions[i] != NULL)
//			delete charPositions[i];
	Clear();
//	delete selBitmap;
//	delete stdBitmap;
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
	wxString *text;
	int len;
	int i;
	byte pi;


	if (n >= items.Count())
		return;

	if (this->IsSelected(n))
	{
		tempDC.SelectObject(selBitmap);
	}
	else
	{
		tempDC.SelectObject(stdBitmap);
	}

	text = GetItem(n);
	len = text->Len();
	for (i = 0; i < len; i++)
	{
		pi = text->GetChar(i);
		if (pi >= 64 && pi < 128)
			pi -= 64;
		if (pi >= 192)			// TODO: ARGH !! Can we get this easier ??
			pi -= 64;
		if (pi >= 64)
			pi -= 64;
		dc.Blit(i * charWidth + rect.x, rect.y, charWidth, charHeigth, &tempDC, pi<<3, 0);
	}
	tempDC.SelectObject(wxNullBitmap);
}


bool CODListBox::SetCBMCharset(byte *buffer, int nLength)
{
	byte *pbInputCharset, *pbOrderedCharset;
	wxBitmap unmaskedStd;
	wxBitmap unmaskedSel;
	wxMask *maskStd;
	wxMask *maskSel;
	wxMemoryDC srcDC;
	wxMemoryDC dstDC;
	int iScreenDepth;
	int iXCnt, iYCnt;
	byte bCharsetByte;


	// allocate memory
	pbInputCharset = (byte*)malloc(0x0800);
	if( pbInputCharset==NULL )
	{
		return false;
	}
	pbOrderedCharset = (byte*)malloc(0x0800);
	if( pbOrderedCharset==NULL )
	{
		free( pbInputCharset );
		return false;
	}

	// construct input charset
	switch( nLength )
	{
	case 2048:
	case 4096:
		// complete charset, no startaddress
		memcpy(pbInputCharset, buffer, 2048);
		break;
	case 2050:
	case 4098:
		// complete charset with startaddress
		memcpy(pbInputCharset, buffer+2, 2048);
		break;
	default:
		free(pbInputCharset);
		free(pbOrderedCharset);
		break;
	}

	// convert charset to bitmap order
	for(iYCnt=0; iYCnt<8; ++iYCnt)
	{
		for(iXCnt=0; iXCnt<256; ++iXCnt)
		{
			bCharsetByte  = pbInputCharset[iYCnt+(iXCnt<<3)];

#ifndef __WIN32__								// don't invert the charset on Win32 systems (my personal flavor)
			bCharsetByte ^= 0xff;
#endif
			bCharsetByte  = abMirrorTab[bCharsetByte];
			pbOrderedCharset[iXCnt+(iYCnt<<8)] = bCharsetByte;
		}
	}

	// get current screen depth
	iScreenDepth = wxDisplayDepth();

	// create a bitmap from the byte array
	wxBitmap charsetBitmapMono((const char*)pbOrderedCharset, 0x0800, 8, 1);

	// free the byte arrays
	free(pbInputCharset);
	free(pbOrderedCharset);

	// create 2 masks from the bitmap
	maskStd = new wxMask(charsetBitmapMono);
	maskSel = new wxMask(charsetBitmapMono);

	unmaskedStd = wxBitmap(0x0800, 8, iScreenDepth);
	unmaskedSel = wxBitmap(0x0800, 8, iScreenDepth);

	stdBitmap = wxBitmap(0x0800, 8, iScreenDepth);
	selBitmap = wxBitmap(0x0800, 8, iScreenDepth);


	srcDC.SelectObject(unmaskedStd);
	srcDC.SetBackground(tBrushStdForeground);
	srcDC.Clear();
	srcDC.SelectObject(wxNullBitmap);

	srcDC.SelectObject(unmaskedSel);
	srcDC.SetBackground(tBrushSelForeground);
	srcDC.Clear();
	srcDC.SelectObject(wxNullBitmap);

	unmaskedStd.SetMask(maskStd);
	unmaskedSel.SetMask(maskSel);

	// clear the destination standard bitmap
	dstDC.SelectObject(stdBitmap);
	dstDC.SetBackground(tBrushStdBackground);
	dstDC.Clear();
	dstDC.SelectObject(wxNullBitmap);

	// clear the destination selected bitmap
	dstDC.SelectObject(selBitmap);
	dstDC.SetBackground(tBrushSelBackground);
	dstDC.Clear();
	dstDC.SelectObject(wxNullBitmap);

	// blit the standard bitmap
	srcDC.SelectObject(unmaskedStd);
	dstDC.SelectObject(stdBitmap);
	dstDC.Blit(0, 0, 0x0800, 8, &srcDC, 0, 0, wxCOPY, true);
	srcDC.SelectObject(wxNullBitmap);
	dstDC.SelectObject(wxNullBitmap);

	srcDC.SelectObject(unmaskedSel);
	dstDC.SelectObject(selBitmap);
	dstDC.Blit(0, 0, 0x0800, 8, &srcDC, 0, 0, wxCOPY, true);
	srcDC.SelectObject(wxNullBitmap);
	dstDC.SelectObject(wxNullBitmap);

	charWidth = 8;
	charHeigth = 8;

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


wxString *CODListBox::GetItem(int index) const
{
	return (wxString*)items[index];
}

CCbmDirectoryEntry* CODListBox::GetEntry(int index) const
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
			wxMask *ptMask;
			bool fOk;

			ptMask = stdBitmap.GetMask();
			fOk = stdBitmap.Ok();
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
