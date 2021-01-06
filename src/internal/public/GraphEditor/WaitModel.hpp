#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QDoubleSpinBox>
#include <QDoubleValidator>

#include "ExecData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

namespace GraphEditor {
    /*!
    ### Model used to make a delay on a quest dialogue or *on the fly.
    This model allow user to select the desired amount of time (seconds) to wait.
    */
    class WaitModel : public NodeDataModel
    {
      Q_OBJECT

    public:
        WaitModel()
        : _spinBox(new QDoubleSpinBox())
        {
            _spinBox->setValue(5.0);
        }

      virtual
      ~WaitModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Wait (seconds)");
      }

      QString
      name() const override
      {
        return QString("Wait");
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

      bool
      hasDynamicPorts(PortType portType) const override {
          return true;
      }

      unsigned int
      nPorts(PortType portType) const override {
          return 1;
      }

      NodeDataType
      dataType(PortType portType, PortIndex portIndex) const override {
        return ExecData().type();
      }

      std::shared_ptr<NodeData>
      outData(PortIndex port) override {
        return std::make_shared<ExecData>();
      }

      void
      setInData(std::shared_ptr<NodeData> data, int i) override
      {
        if (auto numberData = std::dynamic_pointer_cast<ExecData>(data)) {

        }else {
            //Q_EMIT portMoved(PortType::In, i, i);
        }
      }

     QWidget *
     embeddedWidget() override { return _spinBox; }

     QDoubleSpinBox * _spinBox;
    };
}
