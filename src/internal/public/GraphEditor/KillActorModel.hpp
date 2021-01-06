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

namespace GraphEditor {
    /*!
    ### Model used to kill/deactivate an actor inside an UE4 Game Project.
    Needs to load a Character Database before used.
    */
    class KillActorModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      KillActorModel();

      virtual
      ~KillActorModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Kill Character");
      }

      QString
      name() const override
      {
        return QString("Kill Character");
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
}
