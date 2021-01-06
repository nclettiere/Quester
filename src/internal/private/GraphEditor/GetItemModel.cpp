#include <public/GraphEditor/GetItemModel.hpp>
#include <QPainterPath>

GetItemModel::
GetItemModel()
: _getItemWidget(new GetItemWidget())
{

}

unsigned int
GetItemModel::
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
GetItemModel::
dataType(PortType portType, PortIndex portIndex) const
{
    if(portType == PortType::Out)
        return ItemData().type();

  return NodeDataType();
}


std::shared_ptr<NodeData>
GetItemModel::
outData(PortIndex)
{
  return std::make_shared<ItemData>();
}
