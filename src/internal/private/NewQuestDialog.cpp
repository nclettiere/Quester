#include "../public/NewQuestDialog.h"

NewQuestDialog::NewQuestDialog()
       : wxDialog(NULL, -1, "Create New Quest", wxDefaultPosition, wxSize(250, 230))
{

  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  
  wxStaticBox *st = new wxStaticBox(this, -1, wxT(""), 
      wxPoint(5, 5), wxSize(240, 150));

  wxStaticText *stext = new wxStaticText(this, wxID_ANY, "Quest Name", wxPoint(10, 20), wxSize(230, -1), 0);
  wxTextCtrl *tc = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 40), wxSize(230, -1), 0, wxDefaultValidator, wxTextCtrlNameStr);
  
  const char* chars = "Hello world";

  wxString mystring = wxString::FromUTF8(chars);

  wxString choices[] = {mystring};
  wxComboBox *cbo = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), *choices );

  
  //cbo->Set( m_myList );

  wxButton *okButton = new wxButton(this, -1, wxT("Ok"), 
      wxDefaultPosition, wxSize(70, 30));
  wxButton *closeButton = new wxButton(this, -1, wxT("Close"), 
      wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);
  hbox->Add(closeButton, 1, wxLEFT, 5);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_TOP | wxTOP);

  SetSizer(vbox);

  Centre();
  ShowModal();

  Destroy(); 
}