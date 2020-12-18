#ifndef QUESTDIALOGUES_H
#define QUESTDIALOGUES_H

#include <QWidget>

#include <public/dialoguepreview.h>

namespace Ui {
class QuestDialogues;
}

class QuestDialogues : public QWidget
{
    Q_OBJECT

public:
    explicit QuestDialogues(QWidget *parent = nullptr);
    ~QuestDialogues();

private slots:
    void on_btnAddNewMain_clicked();

private:
    Ui::QuestDialogues *ui;
};

#endif // QUESTDIALOGUES_H
