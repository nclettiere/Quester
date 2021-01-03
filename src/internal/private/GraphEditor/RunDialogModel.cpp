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
    if (auto numberData = std::dynamic_pointer_cast<DialogueData>(data))
    {
        if(portIndex > 0) {
            for(size_t i = nPorts(PortType::Out) - 1; i > 0; i--) {
               qDebug("\t--i: %i", i);
               Q_EMIT portRemoved(PortType::Out, i);
            }
            _numberList.clear();

            for(auto& data : numberData->dialogues()) {
                if(_numberList.size() > 0) {
                    if(!(std::find(_numberList.begin(), _numberList.end(), data) != _numberList.end())) {
                        _numberList.push_back(data);
                        Q_EMIT portAdded(PortType::Out, static_cast<int>(_numberList.size()));
                    }
                }else {
                    _numberList.push_back(data);
                    Q_EMIT portAdded(PortType::Out, static_cast<int>(_numberList.size()));
                    //Q_EMIT portAdded(PortType::In, _numberList.size());
                }
            }
        }

    }
    else
    {
        qDebug("Size: %i", static_cast<int>(_numberList.size()));
        //Q_EMIT portRemoved(PortType::In, portIndex);
        for(size_t i = nPorts(PortType::Out) - 1; i > 0; i--) {
           qDebug("\t--i: %i", i);
           Q_EMIT portRemoved(PortType::Out, i);
        }
        _numberList.clear();

        qDebug("Size: %i", _numberList.size());
    }

    //compute();
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
