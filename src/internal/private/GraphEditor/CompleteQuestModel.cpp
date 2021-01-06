#include <public/GraphEditor/CompleteQuestModel.hpp>
#include <QPainterPath>

using namespace GraphEditor;

CompleteQuestModel::
CompleteQuestModel()
: _embeddedDummy(new QWidget())
{
    _embeddedDummy->setFixedWidth(150);
    _embeddedDummy->setFixedHeight(0);
}

unsigned int
CompleteQuestModel::
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
CompleteQuestModel::
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
CompleteQuestModel::
outData(PortIndex)
{
  return std::make_shared<ExecData>();
}

void
CompleteQuestModel::
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
CompleteQuestModel::
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
CompleteQuestModel::
validationState() const
{
  return _modelValidationState;
}

QString
CompleteQuestModel::
validationMessage() const
{
  return _modelValidationError;
}

