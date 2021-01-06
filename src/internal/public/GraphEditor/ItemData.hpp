#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class ItemData : public NodeData
{
public:

  ItemData() {}

  NodeDataType type() const override
  { return NodeDataType {"item", "Item"}; }

};
