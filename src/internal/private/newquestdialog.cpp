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

    QListWidget * questListView = findChild<QListWidget*>("lstQuests");
    QComboBox   * worldComboBox = findChild<QComboBox*>("cboWorlds");

    //for (auto &world : WorldList) // access by reference to avoid copying
    //    worldComboBox->addItem(QString::fromStdString(world.Name));
    //for (auto &quest : QuestList)
    //{
    //    QListWidgetItem * item = new QListWidgetItem();
    //    item->setText(QString::fromStdString(quest.Name));
    //    questListView->addItem(item);
    //}

    connect(worldComboBox, &QComboBox::currentIndexChanged, this, &newQuestDialog::on_cboWorld_currentIndexChanged);
}

void newQuestDialog::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug("Name Text => %s", arg1.toStdString().c_str());
}

void newQuestDialog::on_cboWorld_currentIndexChanged(int index)
{
    qDebug("Combo Index => %s", std::to_string(index).c_str());
}

void newQuestDialog::on_lstQuests_currentRowChanged(int currentRow)
{
    qDebug("List Index => %s", std::to_string(currentRow).c_str());
}

void newQuestDialog::on_newQuestDialog_accepted()
{
    qDebug("READY");
}
