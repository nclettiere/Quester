#include "App.h"

bool MyApp::OnInit() {

    Utils::OpenConsole();

    MyFrame *frame = new MyFrame();
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
MyFrame::MyFrame()
    : wxFrame ( NULL, wxID_ANY, "Hello World" ) {
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
    SetMenuBar ( menuBar );
    CreateStatusBar();
    SetStatusText ( "Welcome to wxWidgets!" );
    Bind ( wxEVT_MENU, &MyFrame::OnNewQuest, this, ID_New );
    Bind ( wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT );
    Bind ( wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT );
}
void MyFrame::OnExit ( wxCommandEvent& event ) {
    Close ( true );
}

void MyFrame::OnAbout ( wxCommandEvent& event ) {
    wxMessageBox ( "This is a wxWidgets Hello World example",
                   "About Hello World", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnNewQuest ( wxCommandEvent& event ) {
    wxString * Worlds = Utils::GetDefaultWorldsAsList(wxGetApp().argv[0].ToStdString());

    NewQuestDialog *custom = new NewQuestDialog ( Worlds );
    custom->Show ( true );
}
