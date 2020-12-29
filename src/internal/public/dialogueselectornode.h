#ifndef DIALOGUESELECTORNODE_H
#define DIALOGUESELECTORNODE_H

#include <QWidget>

#include <public/Globals.h>

namespace Ui {
class DialogueSelectorNode;
}

class DialogueSelectorNode : public QWidget
{
    Q_OBJECT

public:
    explicit DialogueSelectorNode(QWidget *parent = nullptr);
    ~DialogueSelectorNode();

    void SetLocalization(QType::Localization localization);
    QType::Localization GetLocalization();

    void UpdateTextDialogue(QString text);
    QString GetTextDialogue();

    void clear();

private:
    Ui::DialogueSelectorNode *ui;
};

#endif // DIALOGUESELECTORNODE_H
