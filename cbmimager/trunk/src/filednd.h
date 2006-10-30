#ifndef _DNDFILE_H_INCLUDED
#define _DNDFILE_H_INCLUDED

#include "wx/wx.h"
#include "wx/dnd.h"
#include "odlistbox.h"
#include "cbmimager.h"

class DnDFile : public wxFileDropTarget
{
public:
	DnDFile(CBMImager *pOwner);

    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                             const wxArrayString& filenames);
	
	wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);

private:
    CBMImager *m_pOwner;
};


#endif //_DNDFILE_H_INCLUDED

