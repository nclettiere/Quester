#include <public/questgeneralinfo.h>
#include "ui_questgeneralinfo.h"


QuestGeneralInfo::QuestGeneralInfo(Quest *quest, QWidget *parent) :
    QWidget(parent),
    SelectedQuest(quest),
    ui(new Ui::QuestGeneralInfo)
{
    ui->setupUi(this);

    UpdateUI();
}

void QuestGeneralInfo::UpdateUI() {
    if(SelectedQuest == nullptr)
        return;

    ui->tbxId->setText(QString::fromStdString(SelectedQuest->Id.toString()));
    ui->tbxName->setText(QString::fromStdString(SelectedQuest->Name));

    DB::Manager::RetrieveAllWorlds(&WorldList);
    size_t i = 0;
    for (auto &world : WorldList) {
        ui->worldComboBox->addItem(QString::fromStdString(world.Name));
        if(world.Id == SelectedQuest->WorldId)
            ui->worldComboBox->setCurrentIndex(i);
        i++;
    }

    ui->chkMain->setChecked(SelectedQuest->IsMain);
    ui->chkFailable->setChecked(SelectedQuest->IsFailable);
    ui->chkOptional->setChecked(SelectedQuest->IsOptional);
    Quest q  = DB::Manager::RetrieveQuest(SelectedQuest->ParentId);
    InheritedQuest = &q;

    if(InheritedQuest != nullptr)
        ui->lblInheritedQuest->setText(QString::fromStdString(InheritedQuest->Name));
    else
        ui->lblInheritedQuest->setText(QString("None"));
}

void QuestGeneralInfo::on_btnCommit_clicked()
{

}

QuestGeneralInfo::~QuestGeneralInfo()
{
    delete ui;
}
