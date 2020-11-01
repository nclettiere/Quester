#include "../public/NewQuestDialog.h"

#include <iostream>
#include <string>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Path.h>

using namespace std;
using namespace Poco::JSON;

string GetValue ( Object::Ptr aoJsonObject, const char *aszKey ) {
    Poco::Dynamic::Var loVariable;
    string lsReturn;
    string lsKey ( aszKey );

    // Get the member Variable
    //
    loVariable = aoJsonObject->get ( lsKey );

    // Get the Value from the Variable
    //
    lsReturn = loVariable.convert<std::string>();

    return lsReturn;
}

NewQuestDialog::NewQuestDialog(wxString (*Values)[64])
    : wxDialog ( NULL, -1, "Create New Quest", wxDefaultPosition, wxSize ( 450, 450 ) ) {
    
    ComboWorldValues = Values;
    
    wxPanel *panel = new wxPanel ( this, -1 );

    wxBoxSizer *vbox = new wxBoxSizer ( wxVERTICAL );

    wxBoxSizer *hbox1 = new wxBoxSizer ( wxHORIZONTAL );
    wxStaticText *st1 =  new wxStaticText ( panel, wxID_ANY,
                                            wxT ( "Quest Name" ) );

    hbox1->Add ( st1, 0, wxRIGHT, 8 );
    QuestNameText = new wxTextCtrl (panel, ID_QuestName);
    hbox1->Add ( QuestNameText, 1 );

    /////

    wxBoxSizer *hboxCombo = new wxBoxSizer ( wxHORIZONTAL );
    wxStaticText *stCombo =  new wxStaticText ( panel, wxID_ANY, wxT ( "Select World" ) );

    hboxCombo->Add ( stCombo, 0, wxRIGHT, 8 );
    ComboWorlds = new wxComboBox ( panel, ID_ComboWorld, wxT("DEFAULT"), wxDefaultPosition, wxSize ( 240, -1 ), 3, **&ComboWorldValues, wxCB_DROPDOWN |wxCB_READONLY );
    
    ComboWorlds->SetSelection(0);
    
    hboxCombo->Add ( ComboWorlds, 1 );

    vbox->Add ( hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );
    vbox->Add ( hboxCombo, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );

    wxBoxSizer *vboxList = new wxBoxSizer ( wxVERTICAL );

    wxStaticText *stParent =  new wxStaticText ( panel, wxID_ANY, wxT ( "Select Parent Quest" ) );

    vboxList->Add ( stParent, 0, wxEXPAND | wxLEFT | wxTOP, 10 );

    wxArrayString strings;
    strings.Add ( wxT ( "First string" ) );
    strings.Add ( wxT ( "Second string" ) );
    strings.Add ( wxT ( "Third string" ) );
    strings.Add ( wxT ( "Fourth string" ) );
    strings.Add ( wxT ( "Fifth string" ) );
    strings.Add ( wxT ( "Sixth string" ) );

    // Create a ListBox with Single-selection list.
    ListBoxQuest = new wxListBox ( panel, wxID_ANY, wxPoint ( 150, 100 ), wxSize ( 180, 150 ), strings, wxLB_SINGLE );

    //ListBox->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MyFrame::OnListboxRDown), NULL, this);

    vboxList->Add ( ListBoxQuest, ID_QuestList, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );
    
    ButtonClear = new wxButton ( panel, ID_ButtonClear, wxT ( "Clear" ) );
    
    vboxList->Add ( ButtonClear, 0, wxALIGN_RIGHT | wxRIGHT | wxTOP, 10 );
    
    vbox->Add ( vboxList, 0, wxEXPAND | wxRIGHT | wxTOP, 10 );

    wxBoxSizer *hbox2 = new wxBoxSizer ( wxHORIZONTAL );

    vbox->Add ( hbox2, 0, wxLEFT | wxTOP, 10 );

    vbox->Add ( -1, 10 );

    wxBoxSizer *hbox4 = new wxBoxSizer ( wxHORIZONTAL );
    wxRadioButton *cb1 = new wxRadioButton ( panel, wxID_ANY,
            wxT ( "Main" ) );

    hbox4->Add ( cb1 );
    wxRadioButton *cb2 = new wxRadioButton ( panel, wxID_ANY,
            wxT ( "Side" ) );

    hbox4->Add ( cb2, 0, wxLEFT, 10 );
    wxCheckBox *cb3 = new wxCheckBox ( panel, wxID_ANY,
                                       wxT ( "Failable" ) );

    hbox4->Add ( cb3, 0, wxLEFT, 10 );

    wxCheckBox *cb4 = new wxCheckBox ( panel, wxID_ANY,
                                       wxT ( "Optional" ) );

    hbox4->Add ( cb4, 0, wxLEFT, 10 );

    vbox->Add ( hbox4, 0, wxLEFT, 10 );

    vbox->Add ( -1, 25 );

    wxBoxSizer *hbox5 = new wxBoxSizer ( wxHORIZONTAL );
    OkButton = new wxButton ( panel, wxID_ANY, wxT ( "Ok" ) );
    OkButton->Enable(false);
    hbox5->Add ( OkButton, 0 );
    wxButton *btn2 = new wxButton ( panel, wxID_ANY, wxT ( "Close" ) );
    hbox5->Add ( btn2, 0, wxLEFT | wxBOTTOM, 5 );
    vbox->Add ( hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10 );
    
    
    Bind( wxEVT_TEXT, &NewQuestDialog::OnQuestNameChange, this, ID_QuestName );
    Bind( wxEVT_COMBOBOX, &NewQuestDialog::OnQuestNameChange, this, ID_ComboWorld );
    Bind( wxEVT_BUTTON, &NewQuestDialog::OnButtonClearPressed, this, ID_ButtonClear );

    panel->SetSizer ( vbox );
    
    Utils::GenerateCache();

    string lsJson;
    Parser loParser;

    lsJson = "{\"TransactionCode\":\"000000\",\"FileRecordSequenceNumber\":\"111111\",\"TcrSequenceNumber\":\"222222\",\"TransactionRouteIndicator\":\"ABCDE\",\"MerchantEstablishmentNumber\":\"00000000000\",\"MerchantName\":\"BBBBBBBBB\",\"MerchantCity\":\"CCCCCCCC\"}";

    cout << lsJson << endl;

    // Parse the JSON and get the Results
    //
    Poco::Dynamic::Var loParsedJson = loParser.parse ( lsJson );
    Poco::Dynamic::Var loParsedJsonResult = loParser.result();

    // Get the JSON Object
    //
    Object::Ptr loJsonObject = loParsedJsonResult.extract<Object::Ptr>();

    // Get the values for the member variables
    //
    //
    cout << "TransactionCode             " << GetValue ( loJsonObject, "TransactionCode" )               << endl;
    cout << "FileRecordSequenceNumber    " << GetValue ( loJsonObject, "FileRecordSequenceNumber" )      << endl;
    cout << "TcrSequenceNumber           " << GetValue ( loJsonObject, "TcrSequenceNumber" )             << endl;
    cout << "TransactionRouteIndicator   " << GetValue ( loJsonObject, "TransactionRouteIndicator" )     << endl;
    cout << "MerchantEstablishmentNumber " << GetValue ( loJsonObject, "MerchantEstablishmentNumber" )   << endl;
    cout << "MerchantName                " << GetValue ( loJsonObject, "MerchantName" )                  << endl;
    cout << "MerchantCity                " << GetValue ( loJsonObject, "MerchantCity" )                  << endl;


    Centre();
    
    
    ShowModal();

    Destroy();
}


void NewQuestDialog::OnQuestNameChange(wxCommandEvent& event ) {
    if(!QuestNameText->GetValue().IsEmpty() && ComboWorlds->GetSelection() > -1) {
        OkButton->Enable(true);
    }else {
        OkButton->Enable(false);
    }
}


void NewQuestDialog::OnButtonClearPressed(wxCommandEvent& event ) {
    ListBoxQuest->SetSelection(wxNOT_FOUND);
}
