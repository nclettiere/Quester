#ifndef MAKEDIALOGUEWIDGET_H
#define MAKEDIALOGUEWIDGET_H

#include <QWidget>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <public/Globals.h>

namespace Ui {
class MakeDialogueWidget;
}

class MakeDialogueWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MakeDialogueWidget(QWidget *parent = nullptr);
    ~MakeDialogueWidget();

    std::vector<QType::DialogueNodeData> *GetDialogues();

public:
    Q_SIGNAL void OnThisDataChanged();

private slots:
    void on_pushButton_clicked();
    void on_delete_clicked();
    void onTextEdited(QString const &string);

private:
    Ui::MakeDialogueWidget *ui;

    std::vector<QType::DialogueNodeData> DialogueOptions;
};

#endif // MAKEDIALOGUEWIDGET_H
