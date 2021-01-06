#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

namespace GraphEditor {
    /*!
    ### Contains UE4 Game Quest data and other metadata info.
    Needs a UE4 generated Quest Database before usage.
    */
    class QuestData : public NodeData
    {
    public:

      QuestData() {}

      NodeDataType type() const override
      { return NodeDataType {"quest", "Quest"}; }

    };
}
