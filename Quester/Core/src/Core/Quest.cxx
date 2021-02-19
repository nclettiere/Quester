//
// Created by Percebe32 on 2/18/2021.
//

#include "Core/Quest.hxx"

Quest::Quest() :
    _projectUUID(Poco::UUID()),
    _title(""),
    _difficulty(0) {

    GenerateUUID(_uuid);
}

Quest::Quest(const Poco::UUID& projectUUID, const std::string& title, const uint8_t& difficulty) :
    _projectUUID(projectUUID),
    _title(title),
    _difficulty(difficulty) {

    GenerateUUID(_uuid);
}

Poco::UUID Quest::GetUUID() const {
    return _uuid;
}

Poco::UUID Quest::GetProjectUUID() const {
    return _projectUUID;
}

std::string Quest::GetTitle() const {
    return _title;
}

uint8_t Quest::GetDifficulty() const {
    return _difficulty;
}

void Quest::SetProjectUUID(const Poco::UUID& uuid) {
    this->_projectUUID = uuid;
}

void Quest::SetProjectUUID(const std::string& uuid) {
    this->_projectUUID = Poco::UUID(uuid);
}

void Quest::SetTitle(const std::string& title) {
    this->_title = title;
}

void Quest::SetDifficulty(const uint8_t& difficulty) {
    this->_difficulty = difficulty;
}
