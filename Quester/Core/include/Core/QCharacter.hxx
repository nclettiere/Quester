//
// Created by Percebe32 on 2/18/2021.
//

#ifndef QUESTER_QCHARACTER_HXX
#define QUESTER_QCHARACTER_HXX

#include <Poco/UUIDGenerator.h>
#include <Core/QGlobals.hxx>

class QCharacter {
public:
    QCharacter();
    QCharacter(const std::string& name, const CharacterStats& stats);
    ~QCharacter() = default;

    bool operator==(const QCharacter& otherProject) noexcept {
        return ( GetUUID() == otherProject.GetUUID() );
    }
    bool operator!=(const QCharacter& otherProject) noexcept {
        return ( GetUUID() != otherProject.GetUUID() );
    }

    [[nodiscard]] Poco::UUID     GetUUID()  const;
    [[nodiscard]] std::string    GetName()  const;
    [[nodiscard]] const char*    GetName()       ;
    [[nodiscard]] CharacterStats GetStats() const;

    void SetName(const std::string& name);
    void SetStats(const CharacterStats& stats);

private:
    Poco::UUID     _uuid;
    std::string    _name;
    CharacterStats _stats;
};


#endif //QUESTER_QCHARACTER_HXX
