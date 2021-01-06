#ifndef SELECTCHARACTERWIDGET_H
#define SELECTCHARACTERWIDGET_H

#include <QWidget>

namespace Ui {
class SelectCharacterWidget;
}

class SelectCharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCharacterWidget(QWidget *parent = nullptr);
    ~SelectCharacterWidget();

private:
    Ui::SelectCharacterWidget *ui;
};

#endif // SELECTCHARACTERWIDGET_H
