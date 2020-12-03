#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Dynamic/Struct.h>
#include <Poco/Exception.h>
#include <Poco/FileStream.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>
#include <Poco/Data/Session.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>    //GetModuleFileNameW
#include <fcntl.h>
#include <corecrt_io.h>
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

#include <public/Quest.h>

using namespace std;

enum class FileKind { Cache, Quests, DefaultWorlds, Swap };
enum class RemoveKind { NORMAL, RECURSIVE };

class Utils {
public:
    static inline Poco::Data::Session * session = nullptr;

    static std::string GetCacheFilePath();
    static bool GenerateCache();
    static std::string GetEssentialFile ( FileKind Kind );
    static std::tuple<Poco::File, bool> GetFileFrom ( std::string FilePath );
    static std::tuple<Poco::File, bool> GetFileFrom ( Poco::File FilePath );
    static std::vector<std::string> GetDefaultWorldsAsList ( );
    static std::vector<Quest*> GetQuestsAsList();
    static std::vector<Quest*> GetQuestsAsList(Poco::JSON::Array::Ptr Quests);
    static Quest* GetQuestWithId ( Poco::UUID id );
    static Quest* GetQuestWithId ( Poco::UUID id, std::vector<Quest*> QuestsList );
    static std::vector<Quest*> GetQuestWithId ( std::vector<Poco::UUID> QuestsList );
    static bool RemoveQuest(Poco::UUID Id, RemoveKind );
    static void GenerateStructure();
    static std::tuple<bool, std::string> CreateNewQuest(Quest * QuestData);
    static Poco::JSON::Array::Ptr GetQuestAsJSON();
    static std::string GetDBStructure();
    static Poco::Path GetExecutablePath();

    // Windows Only
    static void OpenConsole();

private:
    static std::string GetValue ( Poco::JSON::Object::Ptr JSONObject, const char *Key );
};
