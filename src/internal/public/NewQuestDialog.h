#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <iostream>
#include "Utils.h"

class NewQuestDialog : public wxDialog
{
public:
    NewQuestDialog();
    
private:
    wxTextCtrl *QuestNameText;
    wxButton *OkButton;
    void OnQuestNameChange(wxCommandEvent& event);
};

enum
{
    ID_QuestName = 1
};

