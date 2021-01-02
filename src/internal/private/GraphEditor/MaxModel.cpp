#include <public/GraphEditor/MaxModel.hpp>
#include <algorithm>

MaxModel::MaxModel()
: _dialogue_selector_node(new DialogueSelectorNode())
{
}

unsigned int
MaxModel::
nPorts(QtNodes::PortType portType) const
{
  //if (portType == PortType::Out)
  //   return _numberList.size()+1;
  //else
  //   return 1;

   unsigned int result = 1;

   switch (portType)
   {
     case PortType::In:
       result = 2;
       break;

     case PortType::Out:
       qDebug("Got %i dialogs | 1 exec", _numberList.size());
       result = (_numberList.size() + 1);
       break;
     case PortType::None:
       break;
   }

   return result;
}

bool
MaxModel::
hasDynamicPorts(QtNodes::PortType portType) const
{
    if(portType == PortType::Out)
        return true;

      return false;
}

QtNodes::NodeDataType
MaxModel::
dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
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
            return DialogueData().type();
      }
      break;

    case PortType::None:
      break;
  }
  // FIXME: control may reach end of non-void function [-Wreturn-type]
  return NodeDataType();
}

std::shared_ptr<QtNodes::NodeData>
MaxModel::
outData(QtNodes::PortIndex)
{
  return _result;
}

void
MaxModel::
setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex portIndex)
{

    if (auto numberData = std::dynamic_pointer_cast<DialogueData>(data))
    {
        if(portIndex > 0) {
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

            for(size_t i = 0; i < _numberList.size(); i++) {
                bool found = false;
                for(size_t t = 0; t < numberData->dialogues().size(); t++)
                    if(_numberList[i] == numberData->dialogues()[t])
                        found = true;
                if(!found) {
                    //_numberList.erase(_numberList.begin() + i);
                    //Q_EMIT portRemoved(PortType::Out, i);
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

    compute();
  }

QString
MaxModel::
caption() const
{
  return QStringLiteral("Max");
}

bool
MaxModel::
portCaptionVisible(QtNodes::PortType, QtNodes::PortIndex) const
{
  return true;
}

//QString
//MaxModel::
//portCaption(QtNodes::PortType portType, QtNodes::PortIndex) const
//{
//  switch (portType)
//  {
//    case PortType::In:
//      return QStringLiteral("Exec");
//
//    case PortType::Out:
//      return QStringLiteral("Result");
//
//    default:
//      break;
//  }
//  return QString();
//}

QString
MaxModel::
name() const
{
  return QStringLiteral("Max");
}

//QtNodes::NodeValidationState
//MaxModel::
//validationState() const
//{
//  return _modelValidationState;
//}
//
//QString
//MaxModel::
//validationMessage() const
//{
//  return _modelValidationError;
//}

void
MaxModel::
compute()
{
//  if(_numberList.size() > 0)
//  {
//    _modelValidationState = NodeValidationState::Valid;
//    _modelValidationError = "";
//  }
//  else
//  {
//    _modelValidationState = NodeValidationState::Warning;
//    _modelValidationError = QString("Missing or incorrect inputs");
//  }
//
//  //std::vector<double> numbers;
//  //numbers.reserve(_numberList.size());
//  //
//  //for (auto& portData : _numberList)
//  //{
//  //  auto num = portData.lock();
//  //  if (num && num->isValid())
//  //  {
//  //    numbers.emplace_back(num->number());
//  //  }
//  //}
//  //
//  //if(!numbers.empty())
//  //  _result = std::make_shared<TextData>(*std::max_element(numbers.begin(), numbers.end()));
//  //else
//  //  _result = std::make_shared<TextData>();
//  //
//  Q_EMIT dataUpdated(0);
}

void MaxModel::restore(const QJsonObject& obj)
{
   int in = obj["dynamic_inputs"].toInt();
   if(in > 0){
     // since when node is saved port's number is size+1 with an empty port
     // to restore the correct size of the array it has to be input-1
      _numberList.resize(in-1);
   }
}
