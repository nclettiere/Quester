#include <public/GraphEditor/UpdateQuestValueModel.hpp>
#include <QPainterPath>

UpdateQuestValueModel::
UpdateQuestValueModel()
: _getItemWidget(new UpdateQuestWidget())
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
      result = 2;
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
dataType(PortType portType, PortIndex portIndex) const
{
    switch (portType)
    {
      case PortType::In:
        if(portIndex == 0)
            return ExecData().type();
        else
            return QuestData().type();
        break;

      case PortType::Out:
        return ExecData().type();

      default:
        break;
    }
  return NodeDataType();
}


std::shared_ptr<NodeData>
UpdateQuestValueModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}

void
UpdateQuestValueModel::
compute(bool isQuestConnected)
{
    if(isQuestConnected) {
        _modelValidationState = NodeValidationState::Valid;
        _modelValidationError = QString("");
    }else {
        _modelValidationState = NodeValidationState::Warning;
        _modelValidationError = QString("Missing or incorrect inputs");
    }


    Q_EMIT dataUpdated(0);
}

void
UpdateQuestValueModel::
setInData(std::shared_ptr<NodeData> data, int portIndex)
{
    auto questData = std::dynamic_pointer_cast<QuestData>(data);
    if (questData)
    {
        if(portIndex > 0) {
            compute(true);
        }
    }else {
        if(portIndex > 0) {
            compute(false);
        }
    }
}

QtNodes::NodeValidationState
UpdateQuestValueModel::
validationState() const
{
  return _modelValidationState;
}

QString
UpdateQuestValueModel::
validationMessage() const
{
  return _modelValidationError;
}
