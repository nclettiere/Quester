#ifndef QUESTGENERALINFO_H
#define QUESTGENERALINFO_H

#include <QWidget>

namespace Ui {
class QuestGeneralInfo;
}

class QuestGeneralInfo : public QWidget
{
    Q_OBJECT

public:
    explicit QuestGeneralInfo(QWidget *parent = nullptr);
    ~QuestGeneralInfo();

private:
    Ui::QuestGeneralInfo *ui;
};

#endif // QUESTGENERALINFO_H
