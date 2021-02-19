//
// Created by Percebe32 on 2/18/2021.
//

#ifndef QUESTER_QDIALOGUE_HXX
#define QUESTER_QDIALOGUE_HXX

#include <Poco/UUIDGenerator.h>
#include <Core/QGlobals.hxx>
#include <vector>

class QDialogue {

public:
    QDialogue();
    QDialogue(const Poco::UUID& fromCharacter,
              const Poco::UUID& toCharacter,
              const std::vector<DialogueOption>& options);
    ~QDialogue() = default;

    bool operator==(const QDialogue& otherProject) noexcept {
        return ( GetUUID() == otherProject.GetUUID() );
    }
    bool operator!=(const QDialogue& otherProject) noexcept {
        return ( GetUUID() != otherProject.GetUUID() );
    }

    [[nodiscard]] Poco::UUID                   GetUUID()     const;
    [[nodiscard]] Poco::UUID                   GetFromUUID() const;
    [[nodiscard]] Poco::UUID                   GetToUUID()   const;
    [[nodiscard]] std::vector<DialogueOption>  GetOptions()  const;

    void SetFromUUID(const Poco::UUID& uuid);
    void SetFromUUID(const std::string& uuid);
    void SetToUUID(const Poco::UUID& uuid);
    void SetToUUID(const std::string& uuid);

    void SetOptions(const std::vector<DialogueOption>& options);

private:
    Poco::UUID                  _uuid;
    Poco::UUID                  _fromUUID;
    Poco::UUID                  _toUUID;
    std::vector<DialogueOption> _options;
};


#endif //QUESTER_QDIALOGUE_HXX
