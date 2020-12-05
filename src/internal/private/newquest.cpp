#include <public/mainwindow.h>
#include "./ui_newquest.h"

NewQuest::NewQuest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuest)
{
    ui->setupUi(this);
    QMetaObject::connectSlotsByName(this);
    setWindowFlag(Qt::Dialog, true);
    setWindowModality(Qt::WindowModal);

    PrepareUI();
}

void NewQuest::PrepareUI() {
    DB::ManagerTest::RetrieveAllQuests(&QuestList);

    letName  = findChild<QLineEdit*>("letName");
    lstQuest = findChild<QListWidget*>("tblQuests");

    QListWidgetItem * item = new QListWidgetItem();
    item->setIcon(QIcon("open.xpm"));
    item->setData(0, QVariant("XD"));
    item->setData(1, QVariant("this is ID2"));

    lstQuest->addItem(item);

    //QDialog::connect(lstQuest, &QListWidget::itemSelectionChanged, this, NewQuest::OnListQuestSelectionChanged(lstQuest->selectedItems()[0]));

}

void NewQuest::OnListQuestSelectionChanged(QListWidgetItem * item) {
    QVariant v = item->data(1);
    QString id = v.toString();
    QMessageBox::information(this, tr("Empty Search Field"), id);
}

NewQuest::~NewQuest()
{
    delete ui;
}
