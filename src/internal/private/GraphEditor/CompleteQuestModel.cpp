#include <public/GraphEditor/CompleteQuestModel.hpp>
#include <QPainterPath>

CompleteQuestModel::
CompleteQuestModel()
{

}

unsigned int
CompleteQuestModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


NodeDataType
CompleteQuestModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
CompleteQuestModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
