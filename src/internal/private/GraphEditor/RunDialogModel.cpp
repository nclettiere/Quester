#include <public/GraphEditor/RunDialogModel.hpp>

RunDialogModel::
RunDialogModel()
  : _dialogue_selector_node(new DialogueSelectorNode())
{

}

unsigned int
RunDialogModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
      break;

    case PortType::Out:
      result = (_numberList.size() + 1);
      break;
    case PortType::None:
      break;
  }

  return result;
}

NodeDataType
RunDialogModel::
dataType(PortType portType,
         PortIndex portIndex) const
{
    switch (portType)
    {
      case PortType::In:
        switch (portIndex)
        {
          case 0:
            return ExecData().type();
          case 1:
            return DialogueData().type();
        }
        break;

      case PortType::Out:
        switch (portIndex)
        {
          case 0:
            return ExecData().type();
          default:
              return ExecData().type();
        }
        break;

      case PortType::None:
        break;
    }
  // FIXME: control may reach end of non-void function [-Wreturn-type]
  return NodeDataType();
}


std::shared_ptr<NodeData>
RunDialogModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}

bool
RunDialogModel::
hasDynamicPorts(QtNodes::PortType portType) const
{
  if(portType == PortType::Out)
    return true;

  return false;
}

void
RunDialogModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto dialogueData = std::dynamic_pointer_cast<DialogueData>(data);
    if (dialogueData)
    {
        if(portIndex > 0) {
            for(size_t i = nPorts(PortType::Out) - 1; i > 0; i--) {
               Q_EMIT portRemoved(PortType::Out, i);
            }
            _dialogue_selector_node->UpdateTextDialogue("");
            _numberList.clear();

            uint8_t i = 0;
            for(auto& data : dialogueData->dialogues()) {
                if(i != 0) {
                    if(_numberList.size() > 0) {
                        if(!(std::find(_numberList.begin(), _numberList.end(), data) != _numberList.end())) {
                            _numberList.push_back(data);
                            Q_EMIT portAdded(PortType::Out, static_cast<int>(_numberList.size()));
                        }
                    }else {
                        _numberList.push_back(data);
                        Q_EMIT portAdded(PortType::Out, static_cast<int>(_numberList.size()));
                    }
                }
                i++;
            }

            _dialogue_selector_node->UpdateTextDialogue(dialogueData->dialogues()[0].Text);

            _modelValidationState = NodeValidationState::Valid;
            _modelValidationError = "";
            Q_EMIT dataUpdated(0);
        }
    }
    else
    {
        if(portIndex > 0) {
            for(size_t i = nPorts(PortType::Out) - 1; i > 0; i--) {
               Q_EMIT portRemoved(PortType::Out, i);
            }
            _numberList.clear();
            _dialogue_selector_node->UpdateTextDialogue("");

            _modelValidationState = NodeValidationState::Warning;
            _modelValidationError = QString("Missing or incorrect inputs");
            Q_EMIT dataUpdated(0);
        }
    }
}

QString
RunDialogModel::
portCaption(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      if(portIndex == 0)
        return QStringLiteral("Exec");
      else
        return QStringLiteral("Dialogue");
    case PortType::Out:
      if(portIndex == 0)
        return QStringLiteral("Default Exec");
      else
        return QStringLiteral("Option ") + QString::number(portIndex);

    default:
      break;
  }
  return QString();
}


QtNodes::NodeValidationState
RunDialogModel::
validationState() const
{
  return _modelValidationState;
}

QString
RunDialogModel::
validationMessage() const
{
  return _modelValidationError;
}

void
RunDialogModel::
compute(int dialogueSize)
{
    if(dialogueSize > 0)
    {
      _modelValidationState = NodeValidationState::Valid;
      _modelValidationError = "";
    }
    else
    {
      _modelValidationState = NodeValidationState::Warning;
      _modelValidationError = QString("Missing or incorrect inputs");
    }

    Q_EMIT dataUpdated(0);
}
