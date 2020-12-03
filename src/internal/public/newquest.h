#ifndef NEWQUEST_H
#define NEWQUEST_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>

#include <public/DB/Manager.h>
#include <public/Models/QuestTableModel.h>

#include <iostream>
#include <vector>

namespace Ui {
class NewQuest;
}

class NewQuest : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuest(QWidget *parent = nullptr);
    ~NewQuest();

private:
    Ui::NewQuest *ui;

    std::vector<Quest> QuestList;

    QTableView * tblQuest;
    QLineEdit * letName;

    void PrepareUI();
};

#endif // NEWQUEST_H
