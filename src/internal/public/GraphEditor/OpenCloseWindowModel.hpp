#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTextEdit>

#include "ExecData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class OpenCloseWindowModel : public NodeDataModel
{
  Q_OBJECT

public:
  OpenCloseWindowModel();

  virtual
  ~OpenCloseWindowModel() {}

public:
  QString
  caption() const override
  {
    return QString("Open/Close Window");
  }

  QString
  name() const override
  {
    return QString("Open/Close Window");
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
  { }

 QWidget *
 embeddedWidget() override { return nullptr; }
};
