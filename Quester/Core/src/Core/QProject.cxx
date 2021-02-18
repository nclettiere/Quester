//
// Created by Percebe64 on 2/17/2021.
//

#include <Core/QProject.hxx>

QProject::QProject() {
    auto uuidGenerator = Poco::UUIDGenerator();
    //_uuid = uuidGenerator.create();
    uuidGenerator.createFromName(_uuid, "project");

    spdlog::error("Generated UUID: {0}", _uuid.toString());
}

QProject::QProject(const Poco::UUID& uuid) : _uuid(uuid) {

}