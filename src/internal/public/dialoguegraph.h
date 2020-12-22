#ifndef DIALOGUEGRAPH_H
#define DIALOGUEGRAPH_H

#include <QMainWindow>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>

namespace Ui {
class DialogueGraph;
}

class DialogueGraph : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogueGraph(QWidget *parent = nullptr);
    ~DialogueGraph();

private:
    Ui::DialogueGraph *ui;
};

#endif // DIALOGUEGRAPH_H
