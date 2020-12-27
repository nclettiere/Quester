#include <public/dialoguepreview.h>
#include "ui_dialoguepreview.h"

DialoguePreview::DialoguePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialoguePreview)
{
    ui->setupUi(this);
}

DialoguePreview::~DialoguePreview()
{
    delete ui;
}

std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<TextSourceDataModel>();

  ret->registerModel<TextDisplayDataModel>();

  return ret;
}

void DialoguePreview::on_btnEdit_clicked()
{
    FlowScene scene(registerDataModels());

    FlowView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    QEventLoop loop;
    connect(&view, SIGNAL(done()), &loop, SLOT(quit()));
    loop.exec(); // BLOCKING (non-busy) until quit() is called via the signal done()
}
