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
    : wxFrame ( NULL, wxID_ANY, "Quester", wxDefaultPosition, wxDefaultSize, wxICONIZE ) {
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

    wxDataViewListCtrl *listctrl = new wxDataViewListCtrl ( this, wxID_ANY );
    listctrl->AppendToggleColumn ( "Name" );
    listctrl->AppendTextColumn ( "World" );
    wxVector<wxVariant> data;
    data.push_back ( wxVariant ( true ) );
    data.push_back ( wxVariant ( "row 1" ) );
    listctrl->AppendItem ( data );
    data.clear();
    data.push_back ( wxVariant ( false ) );
    data.push_back ( wxVariant ( "row 3" ) );
    listctrl->AppendItem ( data );
    
    SetMenuBar ( menuBar );
    CreateStatusBar();

    SetStatusText ( "Welcome to Quester!" );
    Bind ( wxEVT_MENU, &QuesterFrame::OnNewQuest, this, ID_New );
    Bind ( wxEVT_MENU, &QuesterFrame::OnAbout, this, wxID_ABOUT );
    Bind ( wxEVT_MENU, &QuesterFrame::OnExit, this, wxID_EXIT );
}
void QuesterFrame::OnExit ( wxCommandEvent& event ) {
    Close ( true );
}

void QuesterFrame::OnAbout ( wxCommandEvent& event ) {
    wxMessageBox ( "This is a wxWidgets Hello World example",
                   "About Hello World", wxOK | wxICON_INFORMATION );
}

void QuesterFrame::OnNewQuest ( wxCommandEvent& event ) {
    wxString * Worlds = Utils::GetDefaultWorldsAsList ( wxGetApp().argv[0].ToStdString() );

    NewQuestDialog *custom = new NewQuestDialog ( Worlds );
    custom->Show ( true );
}
