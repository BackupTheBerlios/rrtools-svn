#pragma once

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "renamedialog.h"
#endif


#include <wx/dialog.h>
#include "Logic/imagebase.h"


#define ID_NEWIMAGEDLG		10009
#define ID_RBD64			10001
#define ID_RBDFI			10002
#define NEWIMAGEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX


class CNewImage :
	public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CNewImage )
    DECLARE_EVENT_TABLE()

public:
	CNewImage(void);
	CNewImage(wxWindow* parent);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = ID_NEWIMAGEDLG, const wxString& caption = _T("Create new Image"),
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = NEWIMAGEDLG_STYLE);

	/// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void OnOK(wxCommandEvent& event);

	CbmImageType GetImageType();

private:
	wxRadioButton *m_rbDFI;
	wxRadioButton *m_rbD64;

	CbmImageType m_imageType;
};
