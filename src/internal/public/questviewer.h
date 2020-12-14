#ifndef QUESTVIEWER_H
#define QUESTVIEWER_H

#include <QMainWindow>
#include <QListView>

namespace Ui {
class QuestViewer;
}

class QuestViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestViewer(QWidget *parent = nullptr);
    ~QuestViewer();

private:
    Ui::QuestViewer *ui;
};

#endif // QUESTVIEWER_H
