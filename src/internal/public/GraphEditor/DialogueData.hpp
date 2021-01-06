#pragma once

#include <nodes/NodeDataModel>
#include <public/Globals.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

namespace GraphEditor {
    /*!
    ### Contains dialogue actual text and metadata information
    */
    class DialogueData : public NodeData
    {
    public:

      DialogueData() {}

      DialogueData(std::vector<QType::DialogueNodeData> dialogues)
      {
          for(auto& data : dialogues) {
             _dialogues.push_back(data);
          }
      }

      NodeDataType type() const override
      { return NodeDataType {"dialogue", "Dialogue"}; }

      std::vector<QType::DialogueNodeData> dialogues() const { return _dialogues; }

    private:

      void addData(Poco::UUID id, QString text) {
        QType::DialogueNodeData inData;
        inData.Id = id;
        inData.Text = text;

        _dialogues.push_back(inData);
      }

      std::vector<QType::DialogueNodeData> _dialogues;
    };
}
