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
    ### Model used to unlock a trophie for the player.
    Needs a generated UE4 Trophie Database before usage.
    */
    class UnlockTrophieModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      UnlockTrophieModel();

      virtual
      ~UnlockTrophieModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Unlock Trophie");
      }

      QString
      name() const override
      {
        return QString("Unlock Trophie");
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
