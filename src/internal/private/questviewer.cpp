#include <public/questviewer.h>
#include "./ui_questviewer.h"

QuestViewer::QuestViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestViewer)
{
    ui->setupUi(this);
}

QuestViewer::~QuestViewer()
{
    delete ui;
}
