#include <public/dialogueselectornode.h>
#include "ui_dialogueselectornode.h"

DialogueSelectorNode::DialogueSelectorNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogueSelectorNode)
{
    ui->setupUi(this);

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);

    setFixedWidth(250);

    this->setContentsMargins(0, 20, 0, 0);

    ui->comboBox->setContentsMargins(0, 20, 0, 0);

    ui->comboBox->addItem(QString("ES"));
    ui->comboBox->addItem(QString("EN"));
    ui->comboBox->addItem(QString("IT"));
}

DialogueSelectorNode::~DialogueSelectorNode()
{
    delete ui;
}

void DialogueSelectorNode::SetLocalization(QType::Localization localization) {
    switch(localization) {
    case QType::Localization::ES:
        ui->comboBox->setCurrentIndex(0);
        break;
    case QType::Localization::EN:
        ui->comboBox->setCurrentIndex(1);
        break;
    case QType::Localization::IT:
        ui->comboBox->setCurrentIndex(2);
        break;
    }


}

QType::Localization DialogueSelectorNode::GetLocalization() {
    return QType::Localization::ES;
}

void DialogueSelectorNode::UpdateTextDialogue(QString text) {
    //ui->lineEdit->setText(text);
}

QString DialogueSelectorNode::GetTextDialogue() {
    return "";
}

void DialogueSelectorNode::clear() {
    ui->lineEdit->clear();
}
