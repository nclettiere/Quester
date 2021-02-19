//
// Created by Percebe64 on 2/17/2021.
//

#include <Core/QProject.hxx>
#include <spdlog/include/spdlog/spdlog.h>

QProject::QProject() {
    GenerateUUID(_uuid);
    spdlog::debug("Generated UUID: {0}", _uuid.toString());
}

QProject::QProject(const std::string& name, const std::string& ue4Version, const std::string& description) :
    _path(Poco::Path()),
    _name(name),
    _ue4Version(ue4Version),
    _description(description) {

     GenerateUUID(_uuid);
     spdlog::debug("Generated Project UUID: {0}", _uuid.toString());
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

bool QProject::SaveProject(const std::string& customPath) {
    if (GetName().empty())
        return false;

    if(customPath.empty()) {
        // Use default save directory

        SetPath(FormatProjectDefaultDir(GetName()));
        //spdlog::debug("Saving Project to: {0}", GetPath().toString());

        GenerateProjectStructure();

        Poco::File pFile(GetProjectFile(GetName()));
        return pFile.createFile();
    }

    return false;
}

bool QProject::GenerateProjectStructure() {
    if (GetName().empty())
        return false;

    if(_path.toString().empty())
        SetPath(FormatProjectDefaultDir(GetName()));
    _path.makeDirectory();

    Poco::Path pChars(FormatProjectCharDir(GetName()));
    Poco::Path pDials(FormatProjectDialDir(GetName()));
    Poco::Path pQuests(FormatProjectQuestDir(GetName()));

    Poco::File pDir(_path);
    Poco::File pCharsDir(pChars);
    Poco::File pDialDir(pDials);
    Poco::File pQuestsDir(pQuests);

    spdlog::debug("Saving Project to: {0}", GetPath().toString());

    if (!pDir.exists())
        pDir.createDirectories();
    if (!pCharsDir.exists())
        pCharsDir.createDirectories();
    if (!pDialDir.exists())
        pDialDir.createDirectories();
    if (!pQuestsDir.exists())
        pQuestsDir.createDirectories();

    return true;
}

