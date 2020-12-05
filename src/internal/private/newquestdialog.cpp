#include <public/newquestdialog.h>
#include "ui_newquestdialog.h"

newQuestDialog::newQuestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newQuestDialog)
{
    ui->setupUi(this);
}

newQuestDialog::~newQuestDialog()
{
    delete ui;
}

void newQuestDialog::on_checkBox_stateChanged(int arg1)
{

}
