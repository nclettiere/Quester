//
// Created by Percebe32 on 2/18/2021.
//

#ifndef QUESTER_QUEST_HXX
#define QUESTER_QUEST_HXX

#include <Poco/UUIDGenerator.h>
#include <Core/QGlobals.hxx>

class Quest {

public:
    Quest();
    Quest(const Poco::UUID& projectUUID, const std::string& title, const uint8_t& difficulty);
    ~Quest() = default;

    bool operator==(const Quest& otherProject) noexcept {
        return ( GetUUID() == otherProject.GetUUID() );
    }
    bool operator!=(const Quest& otherProject) noexcept {
        return ( GetUUID() != otherProject.GetUUID() );
    }

    [[nodiscard]] Poco::UUID  GetUUID()        const;
    [[nodiscard]] Poco::UUID  GetProjectUUID() const;
    [[nodiscard]] std::string GetTitle()       const;
    [[nodiscard]] uint8_t     GetDifficulty()  const;

    void SetProjectUUID(const Poco::UUID& uuid);
    void SetProjectUUID(const std::string& uuid);
    void SetTitle(const std::string& title);
    void SetDifficulty(const uint8_t& difficulty);

private:
    Poco::UUID       _uuid;
    Poco::UUID       _projectUUID;
    std::string      _title;
    uint8_t          _difficulty;
};

#endif //QUESTER_QUEST_HXX
