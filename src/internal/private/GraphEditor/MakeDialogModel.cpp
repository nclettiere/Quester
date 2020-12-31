#include <public/GraphEditor/MakeDialogModel.hpp>
#include <QPainterPath>

MakeDialogModel::
MakeDialogModel()
  : _makeDialogue(new MakeDialogueWidget())
{
  //QPalette palette = _textEdit->palette();
  //palette.setBrush(palette.Window, QBrush(Qt::transparent));
  //_textEdit->setPalette(palette);
  //
  //_textEdit->setStyleSheet("QTextEdit {color: white;margin-top:5px;border-radius: 3px;background-clip: border;background-color: transparent;font: 11pt Vazir;border:3px solid;border-color: rgb(255,95,95);}");
  //

  connect(_makeDialogue, SIGNAL(OnThisDataChanged()), this, SLOT(onTextEdited()));
}


unsigned int
MakeDialogModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = (1);

    default:
      break;
  }

  return result;
}

void
MakeDialogModel::
setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex portIndex)
{


  //compute();
}

void
MakeDialogModel::
onTextEdited()
{
  //QSize size = _textEdit->document()->size().toSize();
  //_textEdit->setFixedHeight( size.height() + 3 );
  //Q_UNUSED(string);

  Q_EMIT dataUpdated(0);
}


NodeDataType
MakeDialogModel::
dataType(PortType, PortIndex) const
{
  return DialogueData().type();
}

std::shared_ptr<NodeData>
MakeDialogModel::
outData(PortIndex)
{
  //return std::make_shared<TextData>(_makeDialogue->toPlainText());
    //DialogueData dlg(*_makeDialogue->GetDialogues());
    //return std::make_shared<DialogueData>(dlg);
    //return std::make_shared<DialogueData>();
    return std::make_shared<DialogueData>(*_makeDialogue->GetDialogues());

}
