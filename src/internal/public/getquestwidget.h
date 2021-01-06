#ifndef GETQUESTWIDGET_H
#define GETQUESTWIDGET_H

#include <QWidget>

namespace Ui {
class GetQuestWidget;
}

class GetQuestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GetQuestWidget(QWidget *parent = nullptr);
    ~GetQuestWidget();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::GetQuestWidget *ui;
};

#endif // GETQUESTWIDGET_H
