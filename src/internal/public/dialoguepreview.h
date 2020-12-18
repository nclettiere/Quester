#ifndef DIALOGUEPREVIEW_H
#define DIALOGUEPREVIEW_H

#include <QWidget>

namespace Ui {
class DialoguePreview;
}

class DialoguePreview : public QWidget
{
    Q_OBJECT

public:
    explicit DialoguePreview(QWidget *parent = nullptr);
    ~DialoguePreview();

private:
    Ui::DialoguePreview *ui;
};

#endif // DIALOGUEPREVIEW_H
