#include <public/GraphEditor/TextDisplayDataModel.hpp>

TextDisplayDataModel::
TextDisplayDataModel()
  : _dialogue_selector_node(new DialogueSelectorNode())
{

}

unsigned int
TextDisplayDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
      break;

    case PortType::Out:
      result = 1;
      break;
    case PortType::None:
      break;
  }

  return result;
}

NodeDataType
TextDisplayDataModel::
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
TextDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}
