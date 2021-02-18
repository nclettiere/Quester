//
// Created by Percebe64 on 2/17/2021.
//

#ifndef QUESTER_QPROJECT_HXX
#define QUESTER_QPROJECT_HXX

#include <Poco/UUIDGenerator.h>
#include <Poco/Path.h>

class QProject {
public:
    QProject();
    QProject(const char* path, std::string& name, std::string& ue4Version, std::string& description);
    explicit QProject(const Poco::UUID& uuid);
    ~QProject() = default;

    Poco::UUID  GetUUID() const;
    Poco::Path  GetPath() const;
    std::string GetName() const;
    std::string GetUE4Version() const;
    std::string GetDescription() const;

private:
    Poco::UUID       _uuid;
    Poco::Path       _path;
    std::string      _name;
    std::string      _ue4Version;
    std::string      _description;
    /*
     * std::vector<Quest*> _quests;
     * std::vector<Dialogue*> _dialogues;
     */
};
#endif //QUESTER_QPROJECT_HXX
