#include <public/questviewer.h>
#include "./ui_questviewer.h"

QuestViewer::QuestViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestViewer)
{
    ui->setupUi(this);

    ui->lstSections->setMinimumWidth(40);
    ui->lstSections->setGeometry(0, 0, 10, 10);
}

QuestViewer::~QuestViewer()
{
    delete ui;
}
