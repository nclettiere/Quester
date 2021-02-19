//
// Created by Percebe32 on 2/18/2021.
//

#ifndef QUESTER_QGLOBALS_HXX
#define QUESTER_QGLOBALS_HXX

#include <Poco/UUIDGenerator.h>
#include <Poco/Path.h>

/*======================[Quester Static Paths]===========================*/

static std::string G_defaultProjectDir = "/QuesterProjects/";
static std::string G_defaultProjectFileExtension = ".qter";

/*=================================[]====================================*/

static const char* G_ue4Versions[7] = { "4.26", "4.25", "4.24", "4.23", "4.22", "4.21", "4.20" };

static void GenerateUUID(Poco::UUID& uuidObj) {
    auto uuidGenerator = Poco::UUIDGenerator();
    uuidObj = uuidGenerator.create();
}

struct CharacterStats {
    CharacterStats() {}
};

struct DialogueOption {
    DialogueOption() {}
};

static std::string GetUserHome() { return Poco::Path::home();}

static std::string GetDefaultProjectDir() {
    return Poco::Path(GetUserHome()).append(G_defaultProjectDir).toString();
}

static std::string FormatProjectDefaultDir(const std::string& pName) {
    return Poco::Path(GetDefaultProjectDir()).append(pName).toString();
}

static std::string FormatProjectCharDir(const std::string& pName) {
    return Poco::Path(GetDefaultProjectDir())
            .append(pName)
            .append("/Characters/")
            .toString();
}

static std::string FormatProjectDialDir(const std::string& pName) {
    return Poco::Path(GetDefaultProjectDir())
            .append(pName)
            .append("/Dialogues/")
            .toString();
}

static std::string FormatProjectQuestDir(const std::string& pName) {
    return Poco::Path(GetDefaultProjectDir())
            .append(pName)
            .append("/Quests/")
            .toString();
}

static std::string GetProjectFile(const std::string& pName) {
    return Poco::Path(FormatProjectDefaultDir(pName))
            .append(pName + G_defaultProjectFileExtension)
            .toString();
}

#endif //QUESTER_QGLOBALS_HXX
