#include "Quester.h"

bool QuesterApp::OnInit() {

    Utils::OpenConsole();

    QuesterFrame *frame = new QuesterFrame();
    frame->Centre();
    frame->Show ( true );

    // Generate Cache & check for first app launch ;
    if ( Utils::GenerateCache() ) {
        wxMessageDialog* dial = new wxMessageDialog ( NULL,
                wxT ( "First use detected" ), wxT ( "Info" ), wxOK );
        dial->ShowModal();
    }

    return true;
}
QuesterFrame::QuesterFrame()
    : wxFrame ( NULL, wxID_ANY, "Quester", wxDefaultPosition, wxSize(500, 450), wxDEFAULT_FRAME_STYLE ) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append ( ID_New, "&New...\tCtrl-N",
                       "Create a new quest file" );
    menuFile->AppendSeparator();
    menuFile->Append ( wxID_EXIT );
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append ( wxID_ABOUT );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append ( menuFile, "&File" );
    menuBar->Append ( menuHelp, "&Help" );

    wxPanel *panel = new wxPanel ( this, wxID_ANY);

    wxBoxSizer *vbox1 = new wxBoxSizer ( wxVERTICAL );
    wxBoxSizer *vbox2 = new wxBoxSizer ( wxVERTICAL );
    wxBoxSizer *hbox1 = new wxBoxSizer ( wxHORIZONTAL );

    NewQuestButton = new wxButton(panel, ID_NewQuestButton, wxT("New Quest"));
    DeleteQuestButton = new wxButton(panel, ID_DeleteQuestButton, wxT("Delete Quest"));
    ViewButton = new wxButton(panel, ID_OkButton, wxT("View"));

    DeleteQuestButton->Enable(false);
    ViewButton->Enable(false);

    ListBoxQuest = new wxListCtrl(panel, ID_ListQuest, wxDefaultPosition, wxSize(-1, 10000), wxLC_REPORT);
    UpdateQuestList();

    wxSizerFlags flagsExpand(1);
    flagsExpand.Align(1).Expand().Border(wxRIGHT, 8);
    hbox1->Add ( ListBoxQuest, flagsExpand);
    
    vbox2->Add(NewQuestButton, 1, wxEXPAND);
    vbox2->Add(-1, 10, wxEXPAND, 10);
    vbox2->Add(ViewButton, 1, wxEXPAND, 0);
    vbox2->Add(DeleteQuestButton, 1, wxEXPAND);
    hbox1->Add ( vbox2, 0, 0, 5 );

    vbox1->Add ( hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8 );

    panel->SetSizerAndFit( vbox1 );

    SetMenuBar ( menuBar );
    CreateStatusBar();

    SetStatusText ( "Welcome to Quester!" );
    Bind(wxEVT_MENU, &QuesterFrame::OnNewQuest, this, ID_New);
    Bind(wxEVT_BUTTON, &QuesterFrame::OnNewQuest, this, ID_NewQuestButton);
    Bind(wxEVT_BUTTON, &QuesterFrame::OnDeleteQuest, this, ID_DeleteQuestButton);
    Bind ( wxEVT_MENU, &QuesterFrame::OnAbout, this, wxID_ABOUT );
    Bind ( wxEVT_MENU, &QuesterFrame::OnExit, this, wxID_EXIT );    
    Bind ( wxEVT_LIST_ITEM_SELECTED, &QuesterFrame::OnQuestListSelection, this, ID_ListQuest );
    Bind ( wxEVT_LIST_ITEM_DESELECTED, &QuesterFrame::OnQuestListDeselection, this, ID_ListQuest );
}
void QuesterFrame::OnExit ( wxCommandEvent& event ) {
    Close ( true );
}

void QuesterFrame::OnAbout ( wxCommandEvent& event ) {
    wxMessageBox ( "This is a wxWidgets Hello World example",
                   "About Hello World", wxOK | wxICON_INFORMATION );
}

void QuesterFrame::UpdateQuestList()
{
    ListBoxQuest->ClearAll();

    ListBoxQuest->InsertColumn(0, _("Name"), wxLIST_FORMAT_LEFT, 100);
    ListBoxQuest->InsertColumn(1, _("World"), wxLIST_FORMAT_LEFT, 100);
    ListBoxQuest->InsertColumn(2, _("Parent Quest"), wxLIST_FORMAT_LEFT, 100);

    ResultQuestList = Utils::GetQuestsAsList();

    for (int i = 0; i < ResultQuestList.size(); i++) {
        ListBoxQuest->InsertItem(i, wxEmptyString);

        ListBoxQuest->SetItem(i, 0, ResultQuestList[i]->Name);
        ListBoxQuest->SetItem(i, 1, ResultQuestList[i]->WorldName);
        ListBoxQuest->SetItem(i, 2, ResultQuestList[i]->ParentQuestName);
    }

    SelectedQuest = nullptr;
    SelectedQuestIndex = -1;

    DeleteQuestButton->Enable(false);
    ViewButton->Enable(false);
}


void QuesterFrame::OnNewQuest ( wxCommandEvent& event ) {
    cout << "Main Executable Path: " << wxGetApp().argv[0].ToStdString() << endl;
    wxString * Worlds = Utils::GetDefaultWorldsAsList ( wxGetApp().argv[0].ToStdString() );

    NewQuestDialog *custom = new NewQuestDialog ( Worlds );
    custom->Show ( true );

    UpdateQuestList();
}

void QuesterFrame::OnDeleteQuest(wxCommandEvent& event)
{
    if (!(SelectedQuestIndex == -1) && !(SelectedQuest == nullptr)) {
        int answer = wxMessageBox("Do you want to delete quest " + SelectedQuest->Name +" ?", "Confirm", wxYES_NO, this);
        if (answer == wxYES) {
            if (Utils::RemoveQuest(SelectedQuest->Id)) {
                wxLogMessage("Quest %s successfuly deleted.", SelectedQuest->Name);
                UpdateQuestList();
            }
            else {
                wxLogError("Error trying to delete quest: %s", SelectedQuest->Name);
            }
        }
        
    }
}

void QuesterFrame::OnQuestListSelection ( wxCommandEvent& event ) {
    long item = -1;
    for ( ;; ) {
        item = ListBoxQuest->GetNextItem ( item,
                                           wxLIST_NEXT_ALL,
                                           wxLIST_STATE_SELECTED );
        if ( item == -1 )
            break;
        // this item is selected - do whatever is needed with it
        Quest* quest = ResultQuestList[item];

        if ( quest != nullptr ) {
            SelectedQuest = quest;
            SelectedQuestIndex = item;
            
            DeleteQuestButton->Enable(true);
            ViewButton->Enable(true);
        }
        //wxLogMessage("Item %s is selected.", quest->Name);
    }
}

void QuesterFrame::OnQuestListDeselection ( wxCommandEvent& event ) {
    SelectedQuest = nullptr;
    SelectedQuestIndex = -1;
    
    DeleteQuestButton->Enable(false);
    ViewButton->Enable(false);
}
