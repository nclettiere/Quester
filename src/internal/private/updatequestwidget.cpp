#include <public/updatequestwidget.h>
#include "ui_updatequestwidget.h"

UpdateQuestWidget::UpdateQuestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateQuestWidget)
{
    ui->setupUi(this);

    setFixedWidth(250); //niceboi//

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);

    ui->combo_ValueType->addItem(QString("String"));
    ui->combo_ValueType->addItem(QString("Vector"));
    ui->combo_ValueType->addItem(QString("Rotator"));
    ui->combo_ValueType->addItem(QString("Int"));
    ui->combo_ValueType->addItem(QString("Float"));
    ui->combo_ValueType->addItem(QString("Name"));
}

UpdateQuestWidget::~UpdateQuestWidget()
{
    delete ui;
}

void UpdateQuestWidget::on_combo_ValueType_currentIndexChanged(int index)
{

}
