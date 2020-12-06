#ifndef NEWQUESTDIALOG_H
#define NEWQUESTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>

#include <iostream>
#include <vector>

#include <public/Utils.h>
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
    std::vector<Quest> QuestList;
    void prepareUi();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::newQuestDialog *ui;
};

#endif // NEWQUESTDIALOG_H
