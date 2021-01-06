#include <public/GraphEditor/RemoveItemModel.hpp>
#include <QPainterPath>

RemoveItemModel::
RemoveItemModel()
: _getItemWidget(new SelectCharacterWidget())
{

}

unsigned int
RemoveItemModel::
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
RemoveItemModel::
dataType(PortType portType, PortIndex portIndex) const
{
    switch (portType)
    {
      case PortType::In:
        if(portIndex == 0)
            return ExecData().type();
        else
            return ItemData().type();
        break;

      case PortType::Out:
        return ExecData().type();

      default:
        break;
    }
  return NodeDataType();
}


std::shared_ptr<NodeData>
RemoveItemModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}

void
RemoveItemModel::
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
RemoveItemModel::
setInData(std::shared_ptr<NodeData> data, int portIndex)
{
    auto questData = std::dynamic_pointer_cast<ItemData>(data);
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
RemoveItemModel::
validationState() const
{
  return _modelValidationState;
}

QString
RemoveItemModel::
validationMessage() const
{
  return _modelValidationError;
}
