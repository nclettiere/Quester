#include <public/questdialogues.h>
#include "ui_questdialogues.h"

QuestDialogues::QuestDialogues(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestDialogues)
{
    ui->setupUi(this);

    QWidget *test = new DialoguePreview(this);
    QWidget *test2 = new DialoguePreview(this);
    QWidget *test3 = new DialoguePreview(this);
    QWidget *test4 = new DialoguePreview(this);
    QWidget *test5 = new DialoguePreview(this);
    QWidget *test6 = new DialoguePreview(this);
    QWidget *test7 = new DialoguePreview(this);
    QWidget *test8 = new DialoguePreview(this);
    ui->Container->addWidget(test);
    ui->Container->addWidget(test2);
    ui->Container->addWidget(test3);
    ui->Container->addWidget(test4);
    ui->Container->addWidget(test5);
    ui->Container->addWidget(test6);
    ui->Container->addWidget(test7);
    ui->Container->addWidget(test8);
}

QuestDialogues::~QuestDialogues()
{
    delete ui;
}

void QuestDialogues::on_btnAddNewMain_clicked()
{

}
