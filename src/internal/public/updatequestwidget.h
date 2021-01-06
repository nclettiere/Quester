#ifndef UPDATEQUESTWIDGET_H
#define UPDATEQUESTWIDGET_H

#include <QWidget>

namespace Ui {
class UpdateQuestWidget;
}

class UpdateQuestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateQuestWidget(QWidget *parent = nullptr);
    ~UpdateQuestWidget();

private slots:
    void on_combo_ValueType_currentIndexChanged(int index);

private:
    Ui::UpdateQuestWidget *ui;
};

#endif // UPDATEQUESTWIDGET_H
