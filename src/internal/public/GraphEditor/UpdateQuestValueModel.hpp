#pragma once

#include <QtCore/QObject>
#include <public/updatequestwidget.h>

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
    ### Model used to update a certain variable of a quest.
    Needs a generated UE4 Quest Database before usage.

    This model allow user to select which kind of value is going to be modified on a specific quest or self.
    */
    class UpdateQuestValueModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      UpdateQuestValueModel();

      virtual
      ~UpdateQuestValueModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Update Quest Value");
      }

      QString
      name() const override
      {
        return QString("Update Quest Value");
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
     embeddedWidget() override { return _getItemWidget; }

     NodeValidationState
     validationState() const override;

     QString
     validationMessage() const override;

     void
     compute(bool isQuestConnected);

    private:

     UpdateQuestWidget *
     _getItemWidget;

     NodeValidationState _modelValidationState = NodeValidationState::Warning;
     QString _modelValidationError = QString("Missing or incorrect inputs");
    };
}
