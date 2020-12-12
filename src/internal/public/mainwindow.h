#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <public/newquestdialog.h>
#include <public/questviewer.h>

#include <public/DB/Manager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_findButton_clicked();

private slots:
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_pushButton_3_released();

private:
    std::vector<Quest> QuestList;
    Quest * SelectedQuest;

    bool viewer_opened;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
