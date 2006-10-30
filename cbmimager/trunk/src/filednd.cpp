
#include "filednd.h"

#include "Logic/imagebase.h"
#include "Logic/d64image.h"
#include "Logic/dfiimage.h"
#include "Logic/cbmsector.h"
#include "Logic/cbmdirectoryentry.h"
#include "Logic/cbmdirectory.h"



DnDFile::DnDFile(CBMImager *pOwner)
{ 
	m_pOwner = pOwner; 
}


bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
    size_t nFiles = filenames.GetCount();
    for ( size_t n = 0; n < nFiles; n++ ) 
	{
		m_pOwner->AddFile(filenames[n]);
    }
    return true;
}


wxDragResult DnDFile::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
	wxUnusedVar(x);
	wxUnusedVar(y);
	if (m_pOwner->GetCurrentImageType() == D16 || m_pOwner->GetCurrentImageType() == NONE || m_pOwner->IsDragSource())
		return wxDragNone;
	return def;
}
