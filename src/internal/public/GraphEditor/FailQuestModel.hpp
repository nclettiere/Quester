#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTextEdit>

#include "ExecData.hpp"
#include "QuestData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

namespace GraphEditor {
    /*!
    ### Model used to fail a quest on the UE4 game.
    */
    class FailQuestModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      FailQuestModel();

      virtual
      ~FailQuestModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Fail Quest");
      }

      QString
      name() const override
      {
        return QString("Fail Quest");
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
      setInData(std::shared_ptr<NodeData>, int) override;

     QWidget *
     embeddedWidget() override { return _embeddedDummy; }

     NodeValidationState
     validationState() const override;

     QString
     validationMessage() const override;

     void
     compute(bool isQuestConnected);

    private:

     QWidget *
     _embeddedDummy;

     NodeValidationState _modelValidationState = NodeValidationState::Warning;
     QString _modelValidationError = QString("Missing or incorrect inputs");
    };
}
