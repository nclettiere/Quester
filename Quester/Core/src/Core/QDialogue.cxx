//
// Created by Percebe32 on 2/18/2021.
//

#include "Core/QDialogue.hxx"

QDialogue::QDialogue() :
    _fromUUID(Poco::UUID()),
    _toUUID(Poco::UUID()),
    _options(std::vector<DialogueOption>()) {
    GenerateUUID(_uuid);
}

QDialogue::QDialogue(const Poco::UUID& fromCharacter, const Poco::UUID& toCharacter, const std::vector<DialogueOption>& options) :
    _fromUUID(fromCharacter),
    _toUUID(toCharacter),
    _options(options) {
    GenerateUUID(_uuid);
}