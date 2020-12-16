#include <public/questdialogues.h>
#include "ui_questdialogues.h"

QuestDialogues::QuestDialogues(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestDialogues)
{
    ui->setupUi(this);
}

QuestDialogues::~QuestDialogues()
{
    delete ui;
}

void QuestDialogues::on_btnAddNewMain_clicked()
{

}
