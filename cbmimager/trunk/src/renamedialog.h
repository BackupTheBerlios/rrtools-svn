#pragma once


#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "renamedialog.h"
#endif


#include "wx/dialog.h"
#include "wx/textctrl.h"


#define ID_RENAMEDLG	10009
#define ID_TEXTBOX		10001
#define RENAMEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX



class CRenameDialog :
	public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CRenameDialog )
    DECLARE_EVENT_TABLE()

public:
	CRenameDialog();
	CRenameDialog(wxWindow* parent, const wxString& value);

    /// Creation
    bool Create( wxWindow* parent, const wxString& value = _T(""), wxWindowID id = ID_RENAMEDLG, const wxString& caption = _T("Rename File"),
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = RENAMEDLG_STYLE);

	/// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void OnOK(wxCommandEvent& event);

	wxString GetText();

private:
	wxTextCtrl *m_TextBox;
	wxString m_value;

	wxString m_ReturnValue;
};


