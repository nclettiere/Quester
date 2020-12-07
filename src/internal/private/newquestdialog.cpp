#include <public/newquestdialog.h>
#include "ui_newquestdialog.h"

newQuestDialog::newQuestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newQuestDialog)
{
    IsMain = 1;
    IsFailable = 0;
    IsOptional = 0;

    ui->setupUi(this);
    prepareUi();
}

newQuestDialog::~newQuestDialog()
{
    delete ui;
}

void newQuestDialog::prepareUi() {
    DB::Manager::RetrieveAllQuests(&QuestList);
    DB::Manager::RetrieveAllWorlds(&WorldList);

    btnCreate = findChild<QPushButton*>("btnCreate");

    QListWidget * questListView = findChild<QListWidget*>("lstQuests");
    QComboBox   * worldComboBox = findChild<QComboBox*>("cboWorld");

    for (auto &world : WorldList) // access by reference to avoid copying
        worldComboBox->addItem(QString::fromStdString(world.Name));
    for (auto &quest : QuestList)
    {
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(QString::fromStdString(quest.Name));
        questListView->addItem(item);
    }
}

void newQuestDialog::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug("Name Text => %s", arg1.toStdString().c_str());
    QuestName = arg1;

    if(QuestName.isEmpty()) {
       btnCreate->setEnabled(false);
    }else {
        if(SelectedWorld != nullptr) {
            btnCreate->setEnabled(true);
        }else {
            btnCreate->setEnabled(false);
        }
    }
}

void newQuestDialog::on_cboWorld_currentIndexChanged(int index)
{
    qDebug("Combo Index => %s", std::to_string(index).c_str());

    if(index != -1) {
        SelectedWorld = &WorldList[index];
    }else {
        SelectedWorld = nullptr;
    }

    if(SelectedWorld == nullptr) {
       btnCreate->setEnabled(false);
    }else {
        if(!QuestName.isEmpty()) {
            btnCreate->setEnabled(true);
        }else {
            btnCreate->setEnabled(false);
        }
    }
}

void newQuestDialog::on_lstQuests_currentRowChanged(int currentRow)
{
    ParentQuest = &QuestList[currentRow];

    qDebug("Parent Index => %s", ParentQuest->GetName());
}

void newQuestDialog::on_radioButton_released()
{
    IsMain = 1;
}

void newQuestDialog::on_radioButton_2_released()
{
    IsMain = 0;
}

void newQuestDialog::on_checkBox_stateChanged(int arg1)
{
    IsFailable = arg1;
}

void newQuestDialog::on_checkBox_2_stateChanged(int arg1)
{
    IsOptional = arg1;
}

void newQuestDialog::on_btnCreate_released()
{
    qDebug("Name == %s | World == %s | ParentQuest == %s | IsMain =- %b | IsFailable == %i | IsOptional == %i",
           QuestName.toStdString().c_str(),
           (SelectedWorld != nullptr) ? SelectedWorld->GetName() : "Not-Selected (invalid)",
           (ParentQuest != nullptr) ? ParentQuest->GetName() : "Not-Selected"),
            IsMain,
            IsFailable,
            IsOptional;
}
