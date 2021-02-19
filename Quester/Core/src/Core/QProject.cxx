//
// Created by Percebe64 on 2/17/2021.
//

#include <Core/QProject.hxx>
#include <spdlog/include/spdlog/spdlog.h>

QProject::QProject() {
    GenerateUUID(_uuid);
    spdlog::debug("Generated UUID: {0}", _uuid.toString());
}

QProject::QProject(const char* path, std::string& name, std::string& ue4Version, std::string& description) :
    _path(Poco::Path(path)),
    _name(name),
    _ue4Version(ue4Version),
    _description(description) {

     GenerateUUID(_uuid);
     spdlog::debug("Generated UUID: {0}", _uuid.toString());
}

QProject::QProject(const Poco::UUID& uuid) : _uuid(uuid) {}


Poco::UUID QProject::GetUUID() const {
    return Poco::UUID();
}

Poco::Path QProject::GetPath() const {
    return _path;
}

std::string QProject::GetName() const {
    return _name;
}

std::string QProject::GetUE4Version() const {
    return _ue4Version;
}

std::string QProject::GetDescription() const {
    return _description;
}

void QProject::SetPath(const std::string &path) {
    _path = Poco::Path(path);
}

void QProject::SetPath(const Poco::Path &path) {
    _path = path;
}

void QProject::SetName(const std::string &name) {
    _name = name;
}

void QProject::SetUE4Version(const std::string &ue4V) {
    _ue4Version = ue4V;
}

void QProject::SetDescription(const std::string &description) {
    _description = description;
}
