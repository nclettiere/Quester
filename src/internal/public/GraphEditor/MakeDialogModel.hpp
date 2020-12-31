#pragma once

#include <QtCore/QObject>
#include <public/GraphEditor/DialogueData.hpp>
#include <public/makedialoguewidget.h>
#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MakeDialogModel : public NodeDataModel
{
  Q_OBJECT

public:
  MakeDialogModel();

  virtual
  ~MakeDialogModel() {}

public:
  QString
  caption() const override
  {
    return QString("Make Dialogue");
  }

  QString
  name() const override
  {
    return QString("MakeDialogue");
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
  setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

  QWidget *
  embeddedWidget() override { return _makeDialogue; }

private slots:
  void
  onTextEdited();

private:
  MakeDialogueWidget * _makeDialogue;
};
