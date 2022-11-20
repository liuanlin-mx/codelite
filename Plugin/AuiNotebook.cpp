#include "AuiNotebook.hpp"

#include <wx/wupdlock.h>

#include "clTabRenderer.h"
#include "editor_config.h"
#include "file_logger.h"

#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <wx/dataobj.h>
#include <wx/defs.h>
#include <wx/dnd.h>
#include <wx/gdicmn.h>
#include <wx/types.h>

clAuiNotebook::clAuiNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                             const wxString& name)
    : wxAuiNotebook(parent, id, pos, size, wxAUI_NB_DEFAULT_STYLE)
{
    SetName(name);
    Initialise(style);
    //SetArtProvider(new wxAuiSimpleTabArt);
}

clAuiNotebook::~clAuiNotebook()
{
    wxDELETE(m_tabContextMenu);
    wxDELETE(m_bitmaps);
    
    Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &clAuiNotebook::OnPageClose, this);
    Unbind(wxEVT_AUINOTEBOOK_PAGE_CHANGING, &clAuiNotebook::OnPageChanging, this);
    Unbind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &clAuiNotebook::OnPageChanged, this);
    Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSED, &clAuiNotebook::OnPageClosed, this);
    Unbind(wxEVT_AUINOTEBOOK_TAB_RIGHT_DOWN, &clAuiNotebook::OnTabRightDown, this);
    Unbind(wxEVT_AUINOTEBOOK_TAB_MIDDLE_DOWN, &clAuiNotebook::OnTabMiddleDown, this);
    //Unbind(wxEVT_AUINOTEBOOK_BUTTON, &clAuiNotebook::OnListButtonDown, this);
    Unbind(wxEVT_AUINOTEBOOK_BG_DCLICK, &clAuiNotebook::OnListButtonDown, this);
    Unbind(wxEVT_CHILD_FOCUS, &clAuiNotebook::OnChildFocusNotebook, this);
    
}

bool clAuiNotebook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                           const wxString& name)
{
    Initialise(style);
    return wxAuiNotebook::Create(parent, id, pos, size, wxAUI_NB_DEFAULT_STYLE);
}

int clAuiNotebook::SetSelection(size_t nPage)
{
    int res = wxAuiNotebook::SetSelection(nPage);
    m_history->Push(wxAuiNotebook::GetCurrentPage());
    return res;
}

int clAuiNotebook::ChangeSelection(size_t nPage)
{
    int res = wxAuiNotebook::ChangeSelection(nPage);
    m_history->Push(GetCurrentPage());
    return res;
}

wxString clAuiNotebook::SavePerspective()
{
    return m_mgr.SavePerspective();
}

bool clAuiNotebook::LoadPerspective(wxString& perspective, bool update)
{
    return m_mgr.LoadPerspective(perspective, update);
}

void clAuiNotebook::AddPage(wxWindow* page, const wxString& label, bool selected, int bmp, const wxString& shortLabel)
{
    if(!page) {
        return;
    }
    if(!page->IsShown()) {
        page->Show();
    }
    if(page->GetParent() != this) {
        page->Reparent(this);
    }
    
    if(!wxAuiNotebook::InsertPage(GetPageCount(), page, label, selected, m_bitmaps->Get(bmp, false))) {
        return;
    }
    DoFinaliseAddPage(page, shortLabel, bmp);
}

bool clAuiNotebook::InsertPage(size_t index, wxWindow* page, const wxString& label, bool selected, int bmp,
                               const wxString& shortLabel)
{
    if(!page) {
        return false;
    }
    if(page->GetParent() != this) {
        page->Reparent(this);
    }
    if(!page->IsShown()) {
        page->Show();
    }
    
    if(!wxAuiNotebook::InsertPage(index, page, label, selected, m_bitmaps->Get(bmp, false))) {
        return false;
    }
    DoFinaliseAddPage(page, shortLabel, bmp);
    return true;
}


int clAuiNotebook::GetPageIndex(wxWindow* page) const
{
    return wxAuiNotebook::GetPageIndex(page);
    /*for(size_t i = 0; i < GetPageCount(); ++i) {
        if(page == GetPage(i)) {
            return static_cast<int>(i);
        }
    }
    return wxNOT_FOUND;*/
}


void clAuiNotebook::BindEvents()
{
    Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &clAuiNotebook::OnPageClose, this);
    Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGING, &clAuiNotebook::OnPageChanging, this);
    Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &clAuiNotebook::OnPageChanged, this);
    Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSED, &clAuiNotebook::OnPageClosed, this);
    Bind(wxEVT_AUINOTEBOOK_TAB_RIGHT_DOWN, &clAuiNotebook::OnTabRightDown, this);
    Bind(wxEVT_AUINOTEBOOK_TAB_MIDDLE_DOWN, &clAuiNotebook::OnTabMiddleDown, this);
    //Bind(wxEVT_AUINOTEBOOK_BUTTON, &clAuiNotebook::OnListButtonDown, this);
    Bind(wxEVT_AUINOTEBOOK_BG_DCLICK, &clAuiNotebook::OnListButtonDown, this);
    Bind(wxEVT_CHILD_FOCUS, &clAuiNotebook::OnChildFocusNotebook, this);
    
}

bool clAuiNotebook::GetPageDetails(wxWindow* page, int& curindex, wxString& label, int& imageId) const
{
    for(size_t i = 0; i < GetPageCount(); ++i) {
        if(page == GetPage(i)) {
            curindex = i;
            label = GetPageText(i);
            imageId = GetPageImage(i);
            return true;
        }
    }
    return false;
}

void clAuiNotebook::OnPageChanged(wxBookCtrlEvent& e)
{
    wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CHANGED);
    event.SetEventObject(this);
    event.SetSelection(GetSelection());
    event.SetOldSelection(e.GetOldSelection());
    GetEventHandler()->ProcessEvent(event);
    m_history->Push(GetCurrentPage());
}

void clAuiNotebook::OnPageChanging(wxBookCtrlEvent& e)
{
    // wrap this event with our own event
    wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CHANGING);
    event.SetEventObject(this);
    event.SetSelection(e.GetSelection());
    event.SetOldSelection(GetSelection());
    GetEventHandler()->ProcessEvent(event);
    if(!event.IsAllowed()) {
        // Vetoed by the user, veto the original event and return
        e.Veto();
        return;
    }
    // Allow changing
    e.Skip();
}

void clAuiNotebook::OnPageClose(wxBookCtrlEvent& e)
{
    wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CLOSING);
    event.SetEventObject(this);
    event.SetSelection(e.GetSelection());
    GetEventHandler()->ProcessEvent(event);
    if(!event.IsAllowed()) {
        // Vetoed
        e.Veto();
        return;
    }
    //e.Skip();
}

void clAuiNotebook::OnPageClosed(wxBookCtrlEvent& e)
{
    wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CLOSED);
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);
}

void clAuiNotebook::OnTabRightDown(wxBookCtrlEvent& e)
{
    
    int index = e.GetSelection();
    if (m_tabContextMenu) {
        if(GetSelection() != index) {
            ChangeSelection(index);
        }
        PopupMenu(m_tabContextMenu);
    } else {
        // fire an event
        wxBookCtrlEvent menuEvent(wxEVT_BOOK_TAB_CONTEXT_MENU);
        menuEvent.SetEventObject(this);
        menuEvent.SetSelection(index);
        GetEventHandler()->ProcessEvent(menuEvent);
    }
}

void clAuiNotebook::OnTabMiddleDown(wxBookCtrlEvent& e)
{
    e.Skip();
}

void clAuiNotebook::OnListButtonDown(wxBookCtrlEvent& e)
{
    clTabInfo::Vec_t tabs;
    GetAllTabs(tabs);

    const int curselection = GetSelection();
    wxMenu menu;
    const int firstTabPageID = 13457;
    int pageMenuID = firstTabPageID;

    // Do we have pages opened?
    if(GetPageCount()) {
        // Optionally make a sorted view of tabs.
        std::vector<size_t> sortedIndexes(GetPageCount());
        {
            // std is C++11 at the moment, so no generalized capture.
            size_t index = 0;
            std::generate(sortedIndexes.begin(), sortedIndexes.end(), [&index]() { return index++; });
        }
        if(EditorConfigST::Get()->GetOptions()->IsSortTabsDropdownAlphabetically()) {
            std::sort(sortedIndexes.begin(), sortedIndexes.end(),
                      [&](size_t i1, size_t i2) { return tabs[i1]->GetLabel().CmpNoCase(tabs[i2]->GetLabel()) < 0; });
        }

        for(auto sortedIndex : sortedIndexes) {
            clTabInfo::Ptr_t tab = tabs[sortedIndex];
            wxWindow* pWindow = tab->GetWindow();
            wxString label = tab->GetLabel();
            wxMenuItem* item = new wxMenuItem(&menu, pageMenuID, label, "", wxITEM_CHECK);
            menu.Append(item);
            item->Check(tab->IsActive());
            menu.Bind(
                wxEVT_MENU,
                [=](wxCommandEvent& event) {
                    int newSelection = GetPageIndex(pWindow);
                    if(newSelection != curselection) {
                        SetSelection(newSelection);
                    }
                },
                pageMenuID);
            pageMenuID++;
        }
    }

    // Let others handle this event as well
    clContextMenuEvent menuEvent(wxEVT_BOOK_FILELIST_BUTTON_CLICKED);
    menuEvent.SetMenu(&menu);
    menuEvent.SetEventObject(this); // The clAuiNotebook
    GetEventHandler()->ProcessEvent(menuEvent);

    if(menu.GetMenuItemCount() == 0) {
        return;
    }

    wxPoint pt(wxNOT_FOUND, wxNOT_FOUND);
    if(pt.x != wxNOT_FOUND) {
        PopupMenu(&menu, pt);
    } else {
        PopupMenu(&menu);
    }
}

void clAuiNotebook::OnChildFocusNotebook(wxChildFocusEvent& evt)
{
    evt.Skip(false);
}

wxWindow* clAuiNotebook::DoUpdateHistoryPreRemove(wxWindow* page)
{
    bool deletingSelection = (page == GetCurrentPage());
    wxWindow* nextSelection = nullptr;
    if(deletingSelection) {
        while(!m_history->GetHistory().empty() && !nextSelection) {
            nextSelection = m_history->PrevPage();
            if(GetPageIndex(nextSelection) == wxNOT_FOUND) {
                // The history contains a tab that no longer exists
                m_history->Pop(nextSelection);
                nextSelection = NULL;
            }
        }
        // It is OK to end up with a null next selection, we will handle it later
    }
    return nextSelection;
}

void clAuiNotebook::DoUpdateHistoryPostRemove(wxWindow* page, bool deletedSelection)
{
    // Choose a new selection
    if(deletedSelection) {
        // Always make sure we have something to select...
        if(!page && GetPageCount()) {
            page = GetPage(0);
        }

        int nextSel = FindPage(page);
        if(nextSel != wxNOT_FOUND) {
            SetSelection(nextSel);
        }
    }
}

bool clAuiNotebook::RemovePage(size_t page, bool notify)
{
    if(GetPageCount() <= page) {
        return false;
    }
    wxWindow* win = GetPage(page);
    if(!win) {
        return false;
    }
    if(notify) {
        wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CLOSING);
        event.SetEventObject(this);
        event.SetSelection(page);
        GetEventHandler()->ProcessEvent(event);
        if(!event.IsAllowed()) {
            // Vetoed
            return false;
        }
    }

    m_userData.erase(win);
    m_history->Pop(win);
    bool deletingSelection = (page == GetSelection());
    wxWindow* nextSelection = DoUpdateHistoryPreRemove(win);
    wxAuiNotebook::RemovePage(page);

    // notify about removal
    if(notify) {
        wxBookCtrlEvent event(wxEVT_BOOK_PAGE_CLOSED);
        event.SetEventObject(this);
        GetEventHandler()->ProcessEvent(event);
    }

    DoUpdateHistoryPostRemove(nextSelection, deletingSelection);
    return true;
}

bool clAuiNotebook::RemovePage(size_t page) { return RemovePage(page, false); }

bool clAuiNotebook::DeletePage(size_t page, bool notify)
{
    if(GetPageCount() <= page) {
        return false;
    }
    wxWindow* win = GetPage(page);
    if(!win) {
        return false;
    }

    // Can we close this page?
    if(notify) {
        wxBookCtrlEvent eventClosing(wxEVT_BOOK_PAGE_CLOSING);
        eventClosing.SetEventObject(this);
        eventClosing.SetSelection(page);
        GetEventHandler()->ProcessEvent(eventClosing);
        if(!eventClosing.IsAllowed()) {
            // Vetoed
            return false;
        }
    }

    bool deletingSelection = (page == GetSelection());
    wxWindow* nextSelection = DoUpdateHistoryPreRemove(win);

    m_history->Pop(win);
    wxAuiNotebook::DeletePage(page);
    m_userData.erase(win);

    // notify about removal
    if(notify) {
        wxBookCtrlEvent eventClosed(wxEVT_BOOK_PAGE_CLOSED);
        eventClosed.SetEventObject(this);
        GetEventHandler()->ProcessEvent(eventClosed);
    }

    DoUpdateHistoryPostRemove(nextSelection, deletingSelection);
    return true;
}

bool clAuiNotebook::DeletePage(size_t page) { return DeletePage(page, true); }


void clAuiNotebook::Initialise(long style)
{
    m_bitmaps = new clBitmapList;
    m_history.reset(new clTabHistory());
    
    size_t auiStyle = wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS;
    m_bookStyle = (style & ~wxWINDOW_STYLE_MASK);
    
    if (m_bookStyle & kNotebook_CloseButtonOnActiveTab) {
        auiStyle |= wxAUI_NB_CLOSE_ON_ALL_TABS;
    }
    if(m_bookStyle & kNotebook_ShowFileListButton) {
        auiStyle |= wxAUI_NB_WINDOWLIST_BUTTON;
    }
    if (m_bookStyle & kNotebook_MouseMiddleClickClosesTab) {
        auiStyle |= wxAUI_NB_MIDDLE_CLICK_CLOSE;
    }
    
    SetWindowStyleFlag(auiStyle);
    BindEvents();
}

void clAuiNotebook::DoFinaliseAddPage(wxWindow* page, const wxString& shortlabel, int bmp)
{
    // do we need to add buton?
    int index = GetPageIndex(page);
    if(index == wxNOT_FOUND) {
        return;
    }
    m_history->Push(page);
    if(m_userData.count(page) == 0) {
        m_userData.insert({ page, {} });
    }
    auto& data = m_userData[page];
    data.tooltip = shortlabel;
    data.bitmap = bmp;
}

void clAuiNotebook::SetTabDirection(wxDirection d)
{
    size_t style = GetWindowStyleFlag();
    style &= ~(wxAUI_NB_TOP | wxAUI_NB_LEFT | wxAUI_NB_RIGHT | wxAUI_NB_BOTTOM);
    
    switch(d) {
    case wxLEFT:
        style |= wxAUI_NB_LEFT;
        break;
    case wxRIGHT:
        style |= wxAUI_NB_RIGHT;
        break;
    case wxBOTTOM:
        style |= wxAUI_NB_BOTTOM;
        break;
    case wxTOP:
        style |= wxAUI_NB_TOP;
        break;
    default:
        style |= wxAUI_NB_TOP;
        break;
    }
    
    SetWindowStyleFlag(style);
    Refresh();
}

void clAuiNotebook::EnableStyle(NotebookStyle style, bool enable)
{
    wxUnusedVar(style);
    wxUnusedVar(enable);
}

wxWindow* clAuiNotebook::GetCurrentPage() const
{
    if(GetSelection() == wxNOT_FOUND) {
        return nullptr;
    }
    return GetPage(GetSelection());
}

bool clAuiNotebook::DeleteAllPages()
{
    if(GetPageCount() == 0) {
        return true;
    }
    while(GetPageCount()) {
        DeletePage(0, false);
    }
    m_history->Clear();
    m_userData.clear();
    return true;
}

void clAuiNotebook::SetPageBitmap(size_t index, int bmp)
{
    wxWindow* win = GetPage(index);
    if(m_userData.count(win) == 0) {
        return;
    }
    m_userData[win].bitmap = bmp;
    wxAuiNotebook::SetPageBitmap(index, m_bitmaps->Get(bmp, false));
    return;
}

wxBitmap clAuiNotebook::GetPageBitmap(size_t index) const
{
    return wxAuiNotebook::GetPageBitmap(index);
}

int clAuiNotebook::GetPageIndex(const wxString& label) const
{
    for(size_t i = 0; i < GetPageCount(); ++i) {
        if(GetPageText(i) == label) {
            return i;
        }
    }
    return wxNOT_FOUND;
}

void clAuiNotebook::GetAllPages(std::vector<wxWindow*>& pages)
{
    for(size_t i = 0; i < GetPageCount(); ++i) {
        pages.push_back(GetPage(i));
    }
}

bool clAuiNotebook::MoveActivePage(int newIndex)
{
    wxWindow* curpage = GetCurrentPage();
    if(curpage == nullptr) {
        return false;
    }

    // avoid flickering
    wxWindowUpdateLocker locker(this);
    wxString label = GetPageText(GetSelection());
    RemovePage(GetSelection());
    InsertPage(newIndex, curpage, label, true);
    return true;
}

clTabHistory::Ptr_t clAuiNotebook::GetHistory() const
{
    // return the history
    return m_history;
}

size_t clAuiNotebook::GetAllTabs(clTabInfo::Vec_t& tabs)
{
    for(size_t i = 0; i < GetPageCount(); ++i) {
        clTabInfo::Ptr_t info(new clTabInfo(nullptr, 0, GetPage(i), GetPageText(i), wxNOT_FOUND));
        tabs.push_back(info);
    }
    return tabs.size();
}


int clAuiNotebook::GetPageBitmapIndex(size_t index) const
{
    wxWindow* win = GetPage(index);
    auto it = m_userData.find(win);
    if(it != m_userData.end()) {
        return it->second.bitmap;
    }
    return wxNOT_FOUND;
}

