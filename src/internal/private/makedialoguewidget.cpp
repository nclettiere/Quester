#include <public/makedialoguewidget.h>
#include "ui_makedialoguewidget.h"

MakeDialogueWidget::MakeDialogueWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeDialogueWidget)
{
    ui->setupUi(this);

    this->setFixedWidth(250);

    QPalette palette = this->palette();
    palette.setBrush(palette.Window, QBrush(Qt::transparent));
    this->setPalette(palette);

    ui->edit0->setProperty("id", QVariant(0));

    connect(ui->edit0, &QLineEdit::textEdited, this, &MakeDialogueWidget::onTextEdited);

    DialogueOptions.push_back(ui->edit0->text());
}

MakeDialogueWidget::~MakeDialogueWidget()
{
    delete ui;
}

void MakeDialogueWidget::on_pushButton_clicked()
{
    int newIndex = DialogueOptions.size();

    QGroupBox *newGroup = new QGroupBox(this);
    newGroup->setTitle(QString("Opcion ") + QString::number(newIndex + 1));
    newGroup->setFont(QFont("Verdana", 9));
    newGroup->setStyleSheet("color: #d5d5d5;");

    QLineEdit *newLine = new QLineEdit(newGroup);
    newLine->setProperty("id", QVariant(newIndex));
    newLine->setStyleSheet("color: black;");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(newLine);
    vbox->addStretch(1);
    newGroup->setLayout(vbox);

    ui->optionLayout->addWidget(newGroup);

    DialogueOptions.push_back(newLine->text());

    connect(newLine, &QLineEdit::textEdited, this, &MakeDialogueWidget::onTextEdited);
    newLine->setText("Default Text");

    Q_EMIT OnThisDataChanged();
}

void MakeDialogueWidget::onTextEdited(QString const &string)
{
    QLineEdit *line = qobject_cast<QLineEdit*>(sender());

    if( line != NULL )
    {
       int id = line->property("id").toInt();
       qDebug("SENDER: %i", id);
       DialogueOptions[id] = line->text();
    }

    Q_EMIT OnThisDataChanged();
}

std::vector<QString> *MakeDialogueWidget::GetDialogues() {
    return &DialogueOptions;
}
