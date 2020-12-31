#ifndef MAKEDIALOGUEWIDGET_H
#define MAKEDIALOGUEWIDGET_H

#include <QWidget>

namespace Ui {
class MakeDialogueWidget;
}

class MakeDialogueWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MakeDialogueWidget(QWidget *parent = nullptr);
    ~MakeDialogueWidget();

    std::vector<QString> *GetDialogues();

public:
    Q_SIGNAL void OnThisDataChanged();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MakeDialogueWidget *ui;

    std::vector<QString> DialogueOptions;

    void onTextEdited(QString const &string);
};

#endif // MAKEDIALOGUEWIDGET_H
