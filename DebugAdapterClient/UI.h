//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: UI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_DEBUGADAPTERCLIENT_UI_BASE_CLASSES_H
#define _CODELITE_DEBUGADAPTERCLIENT_UI_BASE_CLASSES_H

// clang-format off
#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include "clThemedSplitterWindow.h"
#include <wx/dataview.h>
#include "clThemedTreeCtrl.h"
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/toolbar.h>
#include "clToolBar.h"
#include <wx/notebook.h>
#include <wx/button.h>
#include "clThemedListCtrl.h"
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

class DAPMainViewBase : public wxPanel
{
protected:
    clThemedSplitterWindow* m_splitter238;
    wxPanel* m_splitterPage240;
    clThemedTreeCtrl* m_threadsTree;
    wxPanel* m_splitterPage242;
    clThemedTreeCtrl* m_variablesTree;

protected:
public:
    clThemedTreeCtrl* GetThreadsTree() { return m_threadsTree; }
    wxPanel* GetSplitterPage240() { return m_splitterPage240; }
    clThemedTreeCtrl* GetVariablesTree() { return m_variablesTree; }
    wxPanel* GetSplitterPage242() { return m_splitterPage242; }
    clThemedSplitterWindow* GetSplitter238() { return m_splitter238; }
    DAPMainViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxSize(500, 300), long style = wxTAB_TRAVERSAL);
    virtual ~DAPMainViewBase();
};

class DapDebuggerSettingsDlgBase : public wxDialog
{
protected:
    clToolBar* m_toolbar;
    wxPanel* m_panelMain;
    wxNotebook* m_notebook;
    wxStdDialogButtonSizer* m_stdBtnSizer250;
    wxButton* m_button251;
    wxButton* m_button252;

protected:
public:
    clToolBar* GetToolbar() { return m_toolbar; }
    wxNotebook* GetNotebook() { return m_notebook; }
    wxPanel* GetPanelMain() { return m_panelMain; }
    DapDebuggerSettingsDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Settings"),
                               const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                               long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    virtual ~DapDebuggerSettingsDlgBase();
};

class DAPBreakpointsViewBase : public wxPanel
{
protected:
    clThemedListCtrl* m_dvListCtrl;

protected:
public:
    clThemedListCtrl* GetDvListCtrl() { return m_dvListCtrl; }
    DAPBreakpointsViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxSize(500, 300), long style = wxTAB_TRAVERSAL);
    virtual ~DAPBreakpointsViewBase();
};

class DAPTextViewBase : public wxPanel
{
protected:
    wxStyledTextCtrl* m_stcTextView;

protected:
public:
    wxStyledTextCtrl* GetStcTextView() { return m_stcTextView; }
    DAPTextViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxSize(500, 300), long style = wxTAB_TRAVERSAL);
    virtual ~DAPTextViewBase();
};

class DAPOutputViewBase : public wxPanel
{
protected:
protected:
public:
    DAPOutputViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxSize(500, 300), long style = wxTAB_TRAVERSAL);
    virtual ~DAPOutputViewBase();
};

#endif
