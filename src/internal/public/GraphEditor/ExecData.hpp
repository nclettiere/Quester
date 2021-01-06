#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

namespace GraphEditor {
    /*!
    ### Used to create inheritance across nodes
    Contains node Id and next/previous nodes ids.

    Every action node should have at least one executable port.
    */
    class ExecData : public NodeData
    {
    public:

      ExecData() {}

      NodeDataType type() const override
      { return NodeDataType {"exec", "Exec"}; }

    };
}
