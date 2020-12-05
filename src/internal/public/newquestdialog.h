#ifndef NEWQUESTDIALOG_H
#define NEWQUESTDIALOG_H

#include <QDialog>

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
    Ui::newQuestDialog *ui;
};

#endif // NEWQUESTDIALOG_H
