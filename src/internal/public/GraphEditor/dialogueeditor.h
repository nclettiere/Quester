#ifndef DIALOGUEEDITOR_H
#define DIALOGUEEDITOR_H

#include <QMainWindow>

namespace Ui {
class DialogueEditor;
}

class DialogueEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogueEditor(QWidget *parent = nullptr);
    ~DialogueEditor();

private:
    Ui::DialogueEditor *ui;
};

#endif // DIALOGUEEDITOR_H
