#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <Poco/UUID.h>
#include <string>
#include <vector>

#include <public/Globals.h>

class Dialogue
{
public:
    Dialogue();
    ~Dialogue();

    void NewDialogue(QType::DialogueTemplate dialogueTemplate);

private:
    Poco::UUID Id;
    Poco::UUID From;
    Poco::UUID To;

    std::vector<QType::DialogueTemplate> textDialogues;
};

#endif // DIALOGUE_H
