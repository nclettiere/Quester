#include <public/dialoguegraph.h>
#include "ui_dialoguegraph.h"

DialogueGraph::DialogueGraph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogueGraph)
{
    ui->setupUi(this);

    //setStyle();

    QWidget mainWidget;

    auto menuBar    = new QMenuBar();
    auto saveAction = menuBar->addAction("Save..");
    auto loadAction = menuBar->addAction("Load..");

    QVBoxLayout *l = new QVBoxLayout(&mainWidget);
    l->addWidget(menuBar);

}

DialogueGraph::~DialogueGraph()
{
    delete ui;
}
