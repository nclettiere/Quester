#include <public/dialoguepreview.h>
#include "ui_dialoguepreview.h"

DialoguePreview::DialoguePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialoguePreview)
{
    ui->setupUi(this);
}

DialoguePreview::~DialoguePreview()
{
    delete ui;
}
