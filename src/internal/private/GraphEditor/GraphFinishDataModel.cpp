#include <public/GraphEditor/GraphFinishDataModel.hpp>
#include <QPainterPath>

using namespace GraphEditor;

GraphFinishDataModel::
GraphFinishDataModel()
{

}

unsigned int
GraphFinishDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}


NodeDataType
GraphFinishDataModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
GraphFinishDataModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
