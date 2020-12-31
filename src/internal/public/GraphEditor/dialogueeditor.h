#ifndef DIALOGUEEDITOR_H
#define DIALOGUEEDITOR_H

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>

#include <QMainWindow>

#include <nodes/DataModelRegistry>

#include <public/GraphEditor/MakeDialogModel.hpp>
#include <public/GraphEditor/RunDialogModel.hpp>

using QtNodes::DataModelRegistry;
using QtNodes::FlowView;
using QtNodes::FlowScene;

namespace Ui {
class DialogueEditor;
}

class DialogueEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogueEditor(QWidget *parent = nullptr);
    ~DialogueEditor();

private:
    Ui::DialogueEditor *ui;

    static std::shared_ptr<DataModelRegistry>
    registerDataModels();
};

#endif // DIALOGUEEDITOR_H
