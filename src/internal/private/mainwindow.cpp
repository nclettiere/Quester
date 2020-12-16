#include <public/mainwindow.h>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMetaObject::connectSlotsByName(this);
    QPushButton * ui_findButton = findChild<QPushButton*>("pushButton");
    connect(ui_findButton, &QPushButton::released, this, &MainWindow::on_findButton_clicked);

    DB::Manager::RetrieveAllQuests(&QuestList);


    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(QuestList.size());
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("World"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Main Quest"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Is Failable"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Is Optional"));

    for (size_t row=0; row < QuestList.size(); row++) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString(QuestList[row].GetName())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString(QuestList[row].WorldId.toString().c_str())));

        QTableWidgetItem * ItemIsMain = new QTableWidgetItem();
        QTableWidgetItem * ItemIsFailable = new QTableWidgetItem();
        QTableWidgetItem * ItemIsOptional = new QTableWidgetItem();

        ItemIsMain->setTextAlignment(Qt::AlignHCenter);
        ItemIsFailable->setTextAlignment(Qt::AlignHCenter);
        ItemIsOptional->setTextAlignment(Qt::AlignHCenter);

        ItemIsMain->setCheckState(QuestList[row].IsMain ? Qt::Checked : Qt::Unchecked);
        ItemIsFailable->setCheckState(QuestList[row].IsFailable ? Qt::Checked : Qt::Unchecked);
        ItemIsOptional->setCheckState(QuestList[row].IsOptional ? Qt::Checked : Qt::Unchecked);

        ui->tableWidget->setItem(row, 2, ItemIsMain);
        ui->tableWidget->setItem(row, 3, ItemIsFailable);
        ui->tableWidget->setItem(row, 4, ItemIsOptional);
    }

    viewer_opened = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findButton_clicked()
{
    QDialog *openVobDialog = new newQuestDialog(this);
    openVobDialog->show();
}


void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    SelectedQuest = &QuestList[currentRow];
}

void MainWindow::on_pushButton_3_released()
{
    if(!viewer_opened) {
        QuestViewer * qViewer = new QuestViewer(SelectedQuest, this);
        viewer_opened = true;
        qViewer->show();
    }
}
