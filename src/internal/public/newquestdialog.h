#ifndef NEWQUESTDIALOG_H
#define NEWQUESTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QMessageBox>

#include <iostream>
#include <vector>

#include <public/Utils.h>
#include <public/Quest.h>
#include <public/World.h>
#include <public/DB/Manager.h>

namespace Ui {
class newQuestDialog;
}

class newQuestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newQuestDialog(QWidget *parent = nullptr);
    ~newQuestDialog();

private:
    QPushButton * btnCreate;

    std::vector<Quest> QuestList;
    std::vector<World> WorldList;
    QString QuestName;
    World * SelectedWorld = nullptr;
    Quest * ParentQuest = nullptr;

    void prepareUi();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_cboWorld_currentIndexChanged(int index);
    void on_lstQuests_currentRowChanged(int currentRow);

    void on_btnCreate_released();

private:
    Ui::newQuestDialog *ui;
};

#endif // NEWQUESTDIALOG_H
