#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class QuestData : public NodeData
{
public:

  QuestData() {}

  NodeDataType type() const override
  { return NodeDataType {"quest", "Quest"}; }

};
