#ifndef GETITEMWIDGET_H
#define GETITEMWIDGET_H

#include <QWidget>

namespace Ui {
class GetItemWidget;
}

class GetItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GetItemWidget(QWidget *parent = nullptr);
    ~GetItemWidget();

private slots:
    void on_combo_char_currentIndexChanged(int index);

    void on_combo_itemClass_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::GetItemWidget *ui;
};

#endif // GETITEMWIDGET_H
