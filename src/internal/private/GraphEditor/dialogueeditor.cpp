#include <public/GraphEditor/dialogueeditor.h>
#include "ui_dialogueeditor.h"

using namespace GraphEditor;

DialogueEditor::DialogueEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogueEditor)
{
    ui->setupUi(this);

    FlowScene scene(registerDataModels());

    FlowView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();
}

DialogueEditor::~DialogueEditor()
{
    delete ui;
}

std::shared_ptr<DataModelRegistry> DialogueEditor::registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<GraphEditor::MakeDialogModel>();

  ret->registerModel<GraphEditor::RunDialogModel>();

  return ret;
}
