//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: quickdebug.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_FORMBUILDER_QUICKDEBUG_BASE_CLASSES_H
#define _CODELITE_FORMBUILDER_QUICKDEBUG_BASE_CLASSES_H

// clang-format off
#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/imaglist.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/stc/stc.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

// clang-format on

class QuickDebugBase : public wxDialog
{
protected:
    wxNotebook* m_notebook47;
    wxPanel* m_panelLocal;
    wxStaticText* m_staticText3;
    wxChoice* m_choiceDebuggers;
    wxStaticText* m_staticText12;
    wxTextCtrl* m_textCtrlDebuggerExec;
    wxButton* m_buttonBrowseDebugger;
    wxStaticText* m_staticText2;
    wxComboBox* m_ExeFilepath;
    wxButton* m_buttonBrowseExe;
    wxStaticText* m_staticText5;
    wxComboBox* m_WD;
    wxButton* m_buttonBrowseWD;
    wxStaticText* m_staticText4;
    wxTextCtrl* m_textCtrlArgs;
    wxStyledTextCtrl* m_stcStartupCmds;
    wxPanel* m_panelSSH;
    wxChoice* m_choiceSshAccounts;
    wxStaticText* m_staticText62;
    wxTextCtrl* m_textCtrlRemoteDebugger;
    wxButton* m_button66;
    wxStaticText* m_staticText72;
    wxTextCtrl* m_textCtrlRemoteDebuggee;
    wxButton* m_button76;
    wxStaticText* m_staticText78;
    wxTextCtrl* m_textCtrlRemoteWD;
    wxButton* m_button82;
    wxStaticText* m_staticText84;
    wxTextCtrl* m_textCtrlRemoteArgs;
    wxStyledTextCtrl* m_stcRemoteStartupCommands;
    wxStdDialogButtonSizer* m_stdBtnSizer2;
    wxButton* m_buttonOK;
    wxButton* m_buttonCancel1;

protected:
    virtual void OnDebuggerChanged(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSelectAlternateDebugger(wxCommandEvent& event) { event.Skip(); }
    virtual void OnButtonBrowseExe(wxCommandEvent& event) { event.Skip(); }
    virtual void OnButtonBrowseWD(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDebugOverSshUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnRemoteBrowseDebugger(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRemoteBrowedDebuggee(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRemoteBrowseWD(wxCommandEvent& event) { event.Skip(); }
    virtual void OnButtonDebug(wxCommandEvent& event) { event.Skip(); }
    virtual void OnButtonCancel(wxCommandEvent& event) { event.Skip(); }

public:
    wxStaticText* GetStaticText3() { return m_staticText3; }
    wxChoice* GetChoiceDebuggers() { return m_choiceDebuggers; }
    wxStaticText* GetStaticText12() { return m_staticText12; }
    wxTextCtrl* GetTextCtrlDebuggerExec() { return m_textCtrlDebuggerExec; }
    wxButton* GetButtonBrowseDebugger() { return m_buttonBrowseDebugger; }
    wxStaticText* GetStaticText2() { return m_staticText2; }
    wxComboBox* GetExeFilepath() { return m_ExeFilepath; }
    wxButton* GetButtonBrowseExe() { return m_buttonBrowseExe; }
    wxStaticText* GetStaticText5() { return m_staticText5; }
    wxComboBox* GetWD() { return m_WD; }
    wxButton* GetButtonBrowseWD() { return m_buttonBrowseWD; }
    wxStaticText* GetStaticText4() { return m_staticText4; }
    wxTextCtrl* GetTextCtrlArgs() { return m_textCtrlArgs; }
    wxStyledTextCtrl* GetStcStartupCmds() { return m_stcStartupCmds; }
    wxPanel* GetPanelLocal() { return m_panelLocal; }
    wxChoice* GetChoiceSshAccounts() { return m_choiceSshAccounts; }
    wxStaticText* GetStaticText62() { return m_staticText62; }
    wxTextCtrl* GetTextCtrlRemoteDebugger() { return m_textCtrlRemoteDebugger; }
    wxButton* GetButton66() { return m_button66; }
    wxStaticText* GetStaticText72() { return m_staticText72; }
    wxTextCtrl* GetTextCtrlRemoteDebuggee() { return m_textCtrlRemoteDebuggee; }
    wxButton* GetButton76() { return m_button76; }
    wxStaticText* GetStaticText78() { return m_staticText78; }
    wxTextCtrl* GetTextCtrlRemoteWD() { return m_textCtrlRemoteWD; }
    wxButton* GetButton82() { return m_button82; }
    wxStaticText* GetStaticText84() { return m_staticText84; }
    wxTextCtrl* GetTextCtrlRemoteArgs() { return m_textCtrlRemoteArgs; }
    wxStyledTextCtrl* GetStcRemoteStartupCommands() { return m_stcRemoteStartupCommands; }
    wxPanel* GetPanelSSH() { return m_panelSSH; }
    wxNotebook* GetNotebook47() { return m_notebook47; }
    QuickDebugBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Quick Debug"),
                   const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                   long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    virtual ~QuickDebugBase();
};

#endif
