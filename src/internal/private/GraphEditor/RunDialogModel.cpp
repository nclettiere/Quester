#include <public/GraphEditor/RunDialogModel.hpp>

RunDialogModel::
RunDialogModel()
  : _dialogue_selector_node(new DialogueSelectorNode())
{

}

unsigned int
RunDialogModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
      break;

    case PortType::Out:
      result = (_numberList.size() + 1);
      break;
    case PortType::None:
      break;
  }

  return result;
}

NodeDataType
RunDialogModel::
dataType(PortType portType,
         PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      switch (portIndex)
      {
        case 0:
          return ExecData().type();
        case 1:
          return DialogueData().type();
      }
      break;

    case PortType::Out:
      switch (portIndex)
      {
        case 0:
          return ExecData().type();
        //case 1:
        //  return TextData().type();
      }
      break;

    case PortType::None:
      break;
  }
  // FIXME: control may reach end of non-void function [-Wreturn-type]
  return NodeDataType();
}


std::shared_ptr<NodeData>
RunDialogModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}

bool
RunDialogModel::
hasDynamicPorts(QtNodes::PortType portType) const
{
  if(portType == PortType::Out)
    return true;

  return false;
}

void
RunDialogModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
  //auto textData = std::dynamic_pointer_cast<DialogueData>(data);
  //
  //if (textData)
  //{
  //  _dialogue_selector_node->UpdateTextDialogue(textData->dialogues()[0]);
  //}
  //else
  //{
  //  _dialogue_selector_node->clear();
  //}
  //
  //_dialogue_selector_node->adjustSize();

    if (auto numberData = std::dynamic_pointer_cast<DialogueData>(data))
    {
      if (portIndex == static_cast<int>(_numberList.size()))
      {
        _numberList.push_back(numberData);
        Q_EMIT portAdded(PortType::Out, _numberList.size());
        //Q_EMIT portAdded(PortType::In, _numberList.size());
      }
      else
      {
        _numberList[portIndex] = numberData;
      }
    }
    else
    {
        if(portIndex < static_cast<int>(_numberList.size()))
       {
         _numberList.erase(_numberList.begin() + portIndex);
         //Q_EMIT portRemoved(PortType::In, portIndex);
         Q_EMIT portRemoved(PortType::Out, portIndex);
       }
    }
}
