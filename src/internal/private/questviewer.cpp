#include <public/questviewer.h>
#include "./ui_questviewer.h"

QuestViewer::QuestViewer(Quest *quest, QWidget *parent) :
    QMainWindow(parent),
    SelectedQuest(quest),
    ui(new Ui::QuestViewer)
{
    ui->setupUi(this);
    UpdateUI();
}

void QuestViewer::UpdateUI()
{
    QListWidgetItem * itemGeneral = new QListWidgetItem();
    itemGeneral->setText(QString("General"));
    ui->lstSections->addItem(itemGeneral);

    QListWidgetItem * itemDialogueGraph = new QListWidgetItem();
    itemDialogueGraph->setText(QString("Dialogue Graph"));
    ui->lstSections->addItem(itemDialogueGraph);

    QListWidgetItem * itemQuestGraph = new QListWidgetItem();
    itemQuestGraph->setText(QString("Quest Graph"));
    ui->lstSections->addItem(itemQuestGraph);

    itemGeneral->setSelected(true);
}

void QuestViewer::on_lstSections_currentRowChanged(int currentRow)
{
    qDebug("Selection changed %i", currentRow);

    ClearLayout(ui->Content);

    QWidget * newView;

    switch(currentRow) {
        case 0:
            newView = new QuestGeneralInfo(SelectedQuest, this);
        break;
        case 1:
            newView = new QuestDialogues(this);
        break;
    }

    SelectedWidget = newView;
    ui->Content->addWidget(newView);
}

void QuestViewer::ClearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            ClearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

QuestViewer::~QuestViewer()
{
    delete ui;
}
