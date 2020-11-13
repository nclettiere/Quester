#include "../public/QuestEditor.h"

const int triCanvasID = 2000;			// NodeCanvas widget ID

QuestEditor::QuestEditor(wxWindow* parent, const std::string title, const wxPoint& pos,
	const wxSize& size)
	: wxFrame(parent, wxID_ANY, title, pos, size, wxMINIMIZE_BOX | wxCLOSE_BOX | 
		wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN)
{
	NodeCanvas* canvas = new NodeCanvas(this, triCanvasID, nullptr, { 0, 0 },
	{ 800, 800 });
	Fit();
	Centre();
}

QuestEditor::~QuestEditor()
{
}
