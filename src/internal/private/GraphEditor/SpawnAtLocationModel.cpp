#include <public/GraphEditor/SpawnAtLocationModel.hpp>
#include <QPainterPath>

SpawnAtLocationModel::
SpawnAtLocationModel()
{

}

unsigned int
SpawnAtLocationModel::
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
SpawnAtLocationModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
SpawnAtLocationModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
