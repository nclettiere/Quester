#include <public/GraphEditor/AddItemModel.hpp>
#include <QPainterPath>

AddItemModel::
AddItemModel()
{

}

unsigned int
AddItemModel::
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
AddItemModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
AddItemModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
