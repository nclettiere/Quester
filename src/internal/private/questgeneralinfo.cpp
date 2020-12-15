#include <public/questgeneralinfo.h>
#include "ui_questgeneralinfo.h"

QuestGeneralInfo::QuestGeneralInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestGeneralInfo)
{
    ui->setupUi(this);
}

QuestGeneralInfo::~QuestGeneralInfo()
{
    delete ui;
}
