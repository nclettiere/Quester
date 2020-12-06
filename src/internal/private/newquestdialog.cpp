#include <public/newquestdialog.h>
#include "ui_newquestdialog.h"

newQuestDialog::newQuestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newQuestDialog)
{
    ui->setupUi(this);
    prepareUi();
}

newQuestDialog::~newQuestDialog()
{
    delete ui;
}

void newQuestDialog::prepareUi() {
    DB::ManagerTest::RetrieveAllQuests(&QuestList);

    QListWidget * questListView = findChild<QListWidget*>("lstQuests");

    std::string meep = std::to_string(QuestList.size()).c_str();
    for (auto &quest : QuestList) // access by reference to avoid copying
    {
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(QString::fromStdString(quest.Name));
        questListView->addItem(item);
    }
}

void newQuestDialog::on_comboBox_currentIndexChanged(int index)
{
    qDebug("Combo Index => %s", std::to_string(index).c_str());
}

void newQuestDialog::on_listWidget_currentRowChanged(int currentRow)
{
    qDebug("List Index => %s", std::to_string(currentRow).c_str());
}
