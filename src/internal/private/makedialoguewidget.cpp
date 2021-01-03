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

    QType::DialogueNodeData data;
    Poco::UUIDGenerator generator = Poco::UUIDGenerator();
    data.Id = generator.create();
    data.Text = ui->edit0->text();

    DialogueOptions.push_back(data);
}

MakeDialogueWidget::~MakeDialogueWidget()
{
    delete ui;
}

void MakeDialogueWidget::on_pushButton_clicked()
{
    int newIndex = DialogueOptions.size();

    QType::DialogueNodeData data;
    Poco::UUIDGenerator generator = Poco::UUIDGenerator();
    data.Id = generator.create();
    data.Text = QString("Default Text");

    QGroupBox *newGroup = new QGroupBox(this);
    newGroup->setTitle(QString("Opcion ") + QString::number(newIndex + 1));
    newGroup->setFont(QFont("Verdana", 9));
    newGroup->setStyleSheet("color: #d5d5d5;");

    QLineEdit *newLine = new QLineEdit(newGroup);
    newLine->setProperty("id", QVariant(newIndex));
    newLine->setProperty("uuid", QVariant(QString::fromStdString(data.Id.toString())));
    newLine->setStyleSheet("color: black;");

    QPushButton *deleteButton = new QPushButton;
    deleteButton->setProperty("id", QVariant(newIndex));
    deleteButton->setProperty("widget", QVariant::fromValue(newGroup));
    deleteButton->setText("X");
    deleteButton->setFixedWidth(30);
    deleteButton->setStyleSheet("color: black;");
    connect(deleteButton, &QPushButton::clicked, this, &MakeDialogueWidget::on_delete_clicked);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(newLine, 2);
    hbox->addWidget(deleteButton, 0, Qt::AlignRight);

    newGroup->setLayout(hbox);

    ui->optionLayout->addWidget(newGroup);

    DialogueOptions.push_back(data);

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
       DialogueOptions[id].Text = line->text();
    }

    Q_EMIT OnThisDataChanged();
}

std::vector<QType::DialogueNodeData> *MakeDialogueWidget::GetDialogues() {
    return &DialogueOptions;
}

void MakeDialogueWidget::on_delete_clicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if( btn != NULL )
    {
       qDebug("SIZE : %i", DialogueOptions.size());
       int id = btn->property("id").toInt();
       QGroupBox *box = qvariant_cast<QGroupBox*>(btn->property("widget"));
       DialogueOptions.erase(DialogueOptions.begin() + id);
       box->deleteLater();
       qDebug("NEW SIZE : %i", DialogueOptions.size());
    }

    Q_EMIT OnThisDataChanged();
}