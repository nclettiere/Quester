#include <public/GraphEditor/FailQuestModel.hpp>
#include <QPainterPath>

FailQuestModel::
FailQuestModel()
{

}

unsigned int
FailQuestModel::
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
FailQuestModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
FailQuestModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
