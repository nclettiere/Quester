#ifndef QUESTVIEWER_H
#define QUESTVIEWER_H

#include <QMainWindow>
#include <QListView>

#include <public/questdialogues.h>
#include <public/questgeneralinfo.h>

namespace Ui {
class QuestViewer;
}

class QuestViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestViewer(Quest *quest, QWidget *parent = nullptr);
    ~QuestViewer();

private slots:
    void on_lstSections_currentRowChanged(int currentRow);

private:
    Ui::QuestViewer *ui;
    Quest *SelectedQuest;
    QWidget *SelectedWidget;

    void UpdateUI();
    void ClearLayout(QLayout *layout);
};

#endif // QUESTVIEWER_H
