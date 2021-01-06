#include <public/GraphEditor/UnlockTrophieModel.hpp>
#include <QPainterPath>

using namespace GraphEditor;

UnlockTrophieModel::
UnlockTrophieModel()
{

}

unsigned int
UnlockTrophieModel::
nPorts(PortType portType) const
{
  return 1;
}


NodeDataType
UnlockTrophieModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
UnlockTrophieModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
