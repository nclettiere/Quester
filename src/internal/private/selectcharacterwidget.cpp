#include <public/selectcharacterwidget.h>
#include "ui_selectcharacterwidget.h"

SelectCharacterWidget::SelectCharacterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectCharacterWidget)
{
    ui->setupUi(this);

    setFixedWidth(250); //niceboi//

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);
}

SelectCharacterWidget::~SelectCharacterWidget()
{
    delete ui;
}
