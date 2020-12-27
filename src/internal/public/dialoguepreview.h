#ifndef DIALOGUEPREVIEW_H
#define DIALOGUEPREVIEW_H

#include <QWidget>

#include <public/GraphEditor/dialogueeditor.h>

namespace Ui {
class DialoguePreview;
}

class DialoguePreview : public QWidget
{
    Q_OBJECT

public:
    explicit DialoguePreview(QWidget *parent = nullptr);
    ~DialoguePreview();

private slots:
    void on_btnEdit_clicked();

private:
    Ui::DialoguePreview *ui;
};

#endif // DIALOGUEPREVIEW_H
