#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <public/GraphEditor/ExecData.hpp>
#include <public/GraphEditor/DialogueData.hpp>

#include <public/dialogueselectornode.h>

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextDisplayDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  TextDisplayDataModel();

  virtual
  ~TextDisplayDataModel() {}

public:

public:
  QString
  caption() const override
  {
    return QString("Run Dialogue");
  }

  QString
  name() const override
  {
    return QString("Run Dialogue");
  }

public:

  QJsonObject
  save() const override
  {
    QJsonObject modelJson;

    modelJson["name"] = name();

    return modelJson;
  }

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> data, int) override
  {
    auto textData = std::dynamic_pointer_cast<DialogueData>(data);

    if (textData)
    {
      _dialogue_selector_node->UpdateTextDialogue(textData->dialogues()[0]);
    }
    else
    {
      _dialogue_selector_node->clear();
    }

    _dialogue_selector_node->adjustSize();
  }

  QWidget *
  embeddedWidget() override { return _dialogue_selector_node; }

private:

  DialogueSelectorNode * _dialogue_selector_node;
};
