#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DialogueData : public NodeData
{
public:

  DialogueData() {}

  DialogueData(std::vector<QString> const &dialogues)
  {
      for(auto& text : dialogues) {
         _dialogues.push_back(text);
      }
  }

  NodeDataType type() const override
  { return NodeDataType {"dialogue", "Dialogue"}; }

  std::vector<QString> dialogues() const { return _dialogues; }

private:

  void addData(QString text) {
    _dialogues.push_back(text);
  }

  std::vector<QString> _dialogues;
};
