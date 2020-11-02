// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/dataview.h>

#include "internal/public/Messages.h"
#include "internal/public/Utils.h"
#include "internal/public/NewQuestDialog.h"

class QuesterApp : public wxApp
{
public:
    virtual bool OnInit();
};

class QuesterFrame : public wxFrame
{
public:
    QuesterFrame();
private:
    void OnNewQuest(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
enum
{
    ID_New = 1
};

wxIMPLEMENT_APP(QuesterApp);
