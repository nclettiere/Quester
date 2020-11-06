// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/sizer.h>
#include <wx/listctrl.h>

#include "internal/public/Messages.h"
#include "internal/public/Utils.h"
#include "internal/public/NewQuestDialog.h"
#include "internal/public/Quest.h"

class QuesterApp : public wxApp
{
public:
    virtual bool OnInit();
};

class QuesterFrame : public wxFrame
{
public:
    QuesterFrame();
    
    std::vector<Quest*> ResultQuestList;
    Quest * SelectedQuest = nullptr;
    long SelectedQuestIndex = -1;
    
private:
    wxButton   * ViewButton;
    wxButton   * NewQuestButton;
    wxButton   * DeleteQuestButton;
    wxListCtrl * ListBoxQuest;
    
    void OnNewQuest(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnQuestListSelection ( wxCommandEvent& event );
    void OnQuestListDeselection ( wxCommandEvent& event );
};
enum
{
    ID_New = 1,
    ID_ListQuest
};

wxIMPLEMENT_APP(QuesterApp);
