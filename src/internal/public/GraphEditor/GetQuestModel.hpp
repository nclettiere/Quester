#pragma once

#include <QtCore/QObject>
#include <public/getquestwidget.h>

#include "QuestData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class GetQuestModel : public NodeDataModel
{
  Q_OBJECT

public:
  GetQuestModel();

  virtual
  ~GetQuestModel() {}

public:
  QString
  caption() const override
  {
    return QString("Get Quest");
  }

  QString
  name() const override
  {
    return QString("Get Quest");
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
  setInData(std::shared_ptr<NodeData>, int) override
  {}

  QWidget *
  embeddedWidget() override { return _embeddedGetQuestWidget; }

private:

 GetQuestWidget *_embeddedGetQuestWidget;
};
