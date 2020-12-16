#ifndef QUESTGENERALINFO_H
#define QUESTGENERALINFO_H

#include <QWidget>
#include <vector>

#include <public/DB/Manager.h>
#include <public/World.h>
#include <public/Quest.h>

namespace Ui {
class QuestGeneralInfo;
}

class QuestGeneralInfo : public QWidget
{
    Q_OBJECT
public:
    explicit QuestGeneralInfo(Quest *quest, QWidget *parent = nullptr);
    ~QuestGeneralInfo();

private slots:
    void on_btnCommit_clicked();

private:
    Quest * SelectedQuest;
    Quest * InheritedQuest;
    std::vector<World> WorldList;
    void UpdateUI();

private:
    Ui::QuestGeneralInfo *ui;
};

#endif // QUESTGENERALINFO_H
