#include <public/getquestwidget.h>
#include "ui_getquestwidget.h"

GetQuestWidget::GetQuestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetQuestWidget)
{
    ui->setupUi(this);

    setFixedWidth(250); //niceboi//

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);

    ui->comboBox->addItem(QString("This Quest"));
}

GetQuestWidget::~GetQuestWidget()
{
    delete ui;
}

void GetQuestWidget::on_comboBox_currentIndexChanged(int index)
{

}
