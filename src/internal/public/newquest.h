#ifndef NEWQUEST_H
#define NEWQUEST_H

#include <QDialog>

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
};

#endif // NEWQUEST_H
