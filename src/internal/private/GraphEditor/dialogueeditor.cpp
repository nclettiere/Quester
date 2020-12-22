#include <public/GraphEditor/dialogueeditor.h>
#include "ui_dialogueeditor.h"

DialogueEditor::DialogueEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogueEditor)
{
    ui->setupUi(this);
}

DialogueEditor::~DialogueEditor()
{
    delete ui;
}
