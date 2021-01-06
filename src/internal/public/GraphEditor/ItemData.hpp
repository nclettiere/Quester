#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

namespace GraphEditor {
    /*!
    ### Contain Item Unique Id of UE4 Game Project and metadata.
    Needs to load a GameItem Database before used.
    */
    class ItemData : public NodeData
    {
    public:

      ItemData() {}

      NodeDataType type() const override
      { return NodeDataType {"item", "Item"}; }

    };
}
