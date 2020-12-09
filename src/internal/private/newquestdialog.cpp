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

    if(WorldList.size() > 0)
        SelectedWorld = &WorldList[0];
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

void newQuestDialog::on_btnCreate_released()
{
    std::string Name = QuestName.toStdString();

    int IsMain = ui->rdbIsMain->isChecked();
    int IsFailable = ui->chkFailable->isChecked();
    int IsOptional = ui->chkOptional->isChecked();

    qDebug("Name == %s | World == %s | ParentQuest == %s",
           QuestName.toStdString().c_str(),
           (SelectedWorld != nullptr) ? SelectedWorld->GetName() : "Not-Selected (invalid)",
           (ParentQuest != nullptr) ? ParentQuest->GetName() : "Not-Selected");
    qDebug("IsMain == %i | IsFailable == %i | IsOptional == %i",
           IsMain,
           IsFailable,
           IsOptional);

    Quest q;
    q.Name = Name;
    q.WorldId = (SelectedWorld != nullptr) ? SelectedWorld->Id : Poco::UUID();
    q.IsMain = IsMain;
    q.IsFailable = IsFailable;
    q.IsOptional = IsOptional;
    q.ParentId = (ParentQuest != nullptr) ? ParentQuest->Id : Poco::UUID();

    if(DB::Manager::InsertQuest(&q)) {
        QMessageBox::information(this, QString("Success"), QString("Quest successfully created"));
        this->destroy();
    }else {
        QMessageBox::critical(this, QString("Error"), QString("Problem creating quest"));
        this->destroy();
    }
}
