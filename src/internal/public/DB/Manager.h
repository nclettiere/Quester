#pragma once

#include <public/Globals.h>

#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Tuple.h>

#include <stdio.h>
#include <iostream>
#include <vector>

#include <public/Utils.h>
#include <public/Quest.h>
#include <public/World.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

//enum class Database { Quests, Worlds };

namespace DB {
    class Manager
    {
    public:
        Manager();
        static void CreateContext();
        static bool InsertQuest(Quest * questData);
        static Quest RetrieveQuest(Poco::UUID);
        static std::vector<Quest> RetrieveQuests(std::vector<Poco::UUID> idList);
        static void RetrieveAllQuests(std::vector<Quest> * list);
        static void GetRelationships(Poco::UUID Id, std::vector<Quest> * QuestList);
        static bool QuestRemove(Quest Quest); 
        static bool QuestBatchRemove(std::vector<Quest> * QuestList);
        static bool ReplaceReferences(Quest * NewReference, std::vector<Quest> * QuestList);

        static void RetrieveAllWorlds(std::vector<World> * list);
    };
}
