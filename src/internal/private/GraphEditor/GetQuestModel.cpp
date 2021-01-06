#include <public/GraphEditor/GetQuestModel.hpp>
#include <QPainterPath>

using namespace GraphEditor;

GetQuestModel::
GetQuestModel()
: _embeddedGetQuestWidget(new GetQuestWidget())
{

}

unsigned int
GetQuestModel::
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
GetQuestModel::
dataType(PortType, PortIndex) const
{
  return QuestData().type();
}


std::shared_ptr<NodeData>
GetQuestModel::
outData(PortIndex)
{
  return std::make_shared<QuestData>();
}
