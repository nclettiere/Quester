//
// Created by Percebe64 on 2/17/2021.
//

#ifndef QUESTER_QPROJECT_HXX
#define QUESTER_QPROJECT_HXX

#include <Poco/UUIDGenerator.h>
#include <spdlog/spdlog-inl.h>

class QProject {
public:
    QProject();
    explicit QProject(const Poco::UUID& uuid);
    ~QProject() = default;
private:
    Poco::UUID _uuid;
};


#endif //QUESTER_QPROJECT_HXX
