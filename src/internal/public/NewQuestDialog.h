#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>
#include "Utils.h"

class NewQuestDialog : public wxDialog {
    wxString (*ComboWorldValues)[64];
private:
    wxTextCtrl * QuestNameText;
    wxButton   * OkButton;
    wxComboBox * ComboWorlds;
    wxButton   * ButtonClear;
    wxListBox  * ListBoxQuest;

    void OnQuestNameChange ( wxCommandEvent& event );
    void OnButtonClearPressed ( wxCommandEvent& event );
public:
    NewQuestDialog(wxString (*Values)[64]);
};

enum {
    ID_QuestName = 1,
    ID_ComboWorld,
    ID_QuestList,
    ID_ButtonClear
};

