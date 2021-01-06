#include <public/GraphEditor/OpenCloseWindowModel.hpp>
#include <QPainterPath>

OpenCloseWindowModel::
OpenCloseWindowModel()
{

}

unsigned int
OpenCloseWindowModel::
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
OpenCloseWindowModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
OpenCloseWindowModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
