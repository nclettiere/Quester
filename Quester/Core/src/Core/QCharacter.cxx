//
// Created by Percebe32 on 2/18/2021.
//

#include "Core/QCharacter.hxx"

QCharacter::QCharacter() :
    _name("name"),
    _stats(CharacterStats()) {
    GenerateUUID(_uuid);
}

QCharacter::QCharacter(const std::string& name, const CharacterStats& stats) :
    _name(name),
    _stats(stats) {
    GenerateUUID(_uuid);
}

Poco::UUID QCharacter::GetUUID() const {
    return _uuid;
}

std::string QCharacter::GetName() const {
    return _name;
}

const char* QCharacter::GetName() {
    return _name.c_str();
}

CharacterStats QCharacter::GetStats() const {
    return _stats;
}

void QCharacter::SetName(const std::string &name) {
    this->_name = name;
}

void QCharacter::SetStats(const CharacterStats &stats) {
    this->_stats = stats;
}
