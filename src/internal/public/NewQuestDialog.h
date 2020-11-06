#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/listctrl.h>

#include <iostream>
#include <Poco/UUIDGenerator.h>
#include "Utils.h"

class NewQuestDialog : public wxDialog {
    wxString * ComboWorldValues;
private:
    wxTextCtrl    * QuestNameText;
    wxButton      * OkButton;
    wxComboBox    * ComboWorlds;
    wxButton      * ButtonClear;
    wxListCtrl     * ListBoxQuest;
    wxRadioButton * MainRadio;
    wxRadioButton * SideRadio;
    wxCheckBox    * FailableCheck;
    wxCheckBox    * OptionalCheck;

    std::vector<Quest*> ResultQuestList;
    Quest * SelectedQuest = nullptr;
    long SelectedQuestIndex = -1;
    
    bool IsMain;
    bool IsFailable;
    bool IsOptional;

    void OnQuestNameChange ( wxCommandEvent& event );
    void OnButtonClearPressed ( wxCommandEvent& event );
    void OnOkButtonPressed ( wxCommandEvent& event );
    void OnFlagsChanged ( wxCommandEvent& event );
    void OnQuestListSelection(wxCommandEvent& event);
    void OnQuestListDeselection(wxCommandEvent& event);

public:
    NewQuestDialog ( wxString * Values );
};

enum {
    ID_QuestName = 1,
    ID_OkButton,
    ID_ComboWorld,
    ID_QuestList,
    ID_ButtonClear,
    ID_Flags_Radio,
    ID_Flags_Check
};

