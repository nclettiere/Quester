#include <public/getitemwidget.h>
#include "ui_getitemwidget.h"

GetItemWidget::GetItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetItemWidget)
{
    ui->setupUi(this);

    setFixedWidth(250); //niceboi//

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);
}

GetItemWidget::~GetItemWidget()
{
    delete ui;
}

void GetItemWidget::on_combo_char_currentIndexChanged(int index)
{

}

void GetItemWidget::on_combo_itemClass_currentIndexChanged(int index)
{

}

void GetItemWidget::on_spinBox_valueChanged(int arg1)
{

}
