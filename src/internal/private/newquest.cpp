#include <public/mainwindow.h>
#include "ui_newquest.h"

NewQuest::NewQuest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuest)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Dialog, true);
    setWindowModality(Qt::WindowModal);
}

NewQuest::~NewQuest()
{
    delete ui;
}
