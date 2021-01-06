#include <public/GraphEditor/UpdateQuestValueModel.hpp>
#include <QPainterPath>

UpdateQuestValueModel::
UpdateQuestValueModel()
{

}

unsigned int
UpdateQuestValueModel::
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
UpdateQuestValueModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
UpdateQuestValueModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
