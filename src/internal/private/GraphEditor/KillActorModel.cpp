#include <public/GraphEditor/KillActorModel.hpp>
#include <QPainterPath>

using namespace GraphEditor;

KillActorModel::
KillActorModel()
{

}

unsigned int
KillActorModel::
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
KillActorModel::
dataType(PortType, PortIndex) const
{
  return ExecData().type();
}


std::shared_ptr<NodeData>
KillActorModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}
