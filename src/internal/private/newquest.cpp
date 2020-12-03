#include <public/mainwindow.h>
#include "ui_newquest.h"

NewQuest::NewQuest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuest)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Dialog, true);
    setWindowModality(Qt::WindowModal);
    QMetaObject::connectSlotsByName(this);

    PrepareUI();
}

void NewQuest::PrepareUI() {
    DB::ManagerTest::RetrieveAllQuests(&QuestList);
    QuestTableModel questModel;

    letName  = findChild<QLineEdit*>("letName");
    tblQuest = findChild<QTableView*>("tblQuests");

    tblQuest->setModel(&questModel);
}

NewQuest::~NewQuest()
{
    delete ui;
}
