#include <public/DB/Manager.h>

void DB::Manager::CreateContext() {
    try {
        // Ensures basic structure of database
        std::cout <<  Utils::GetDBStructure() << std::endl;
        *Utils::session << Utils::GetDBStructure(), now;
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
}

DB::Manager::Manager() {
    try {
        CreateContext();
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
}

bool DB::Manager::InsertQuest(Quest * questData) {
    try {
        Statement insert(*Utils::session);

        std::string qId = questData->Id.toString();
        std::string qParentId = questData->ParentId.toString();
        insert << "INSERT INTO Quest VALUES(?, ?, ?, ?, ?, ?, ?)",
            use(qId),
            use(questData->Name),
            use(questData->WorldName),
            use(questData->IsMain),
            use(questData->IsFailable),
            use(questData->IsOptional),
            use(qParentId);

        insert.execute();
    }catch( Poco::Exception ex) {
        return false;
    }

    return true;
}

Quest  DB::Manager::RetrieveQuest(Poco::UUID id) {
    if(id != Poco::UUID()) {
        Statement select(*Utils::session);
        QType::TempQuest tmp;
        select << "SELECT * FROM Quest WHERE Id='"+id.toString()+"'", 
            into(tmp);
        select.execute();
        return Quest(tmp);
    }else {
      // Has no parent
      return Quest();
    }
}

std::vector<Quest> DB::Manager::RetrieveQuests(std::vector<Poco::UUID> idList){
    return std::vector<Quest>();
}

void DB::Manager::RetrieveAllQuests(std::vector<Quest> * list) {
    Statement select(*Utils::session);
    std::vector<QType::TempQuest> quests;

    select << "SELECT * FROM Quest;",
    into(quests);


    while (!select.done())
    {
        select.execute();
        for(size_t i=0;i<quests.size();i++) {
            list->push_back(Quest(quests[i]));
        }
    }
}

void DB::Manager::GetRelationships(Poco::UUID Id, std::vector<Quest> * QuestList) {
    Statement select(*Utils::session);
    std::vector<QType::TempQuest> quests;
    select << "SELECT * FROM Quest WHERE ParentId='"+Id.toString()+"';",
    into(quests);

    while (!select.done())
    {
        select.execute();
        for(size_t i=0;i<quests.size();i++)
            QuestList->push_back(Quest(quests[i]));
    }
}

bool DB::Manager::QuestRemove(Quest Quest) {
    try {
        *Utils::session << "DELETE FROM Quest WHERE Id='"+Quest.Id.toString()+"';", now;
    }catch(Poco::Exception ex) {
        std::cout << ex.displayText() << std::endl;
        return false;
    }

    return true;
}
bool DB::Manager::QuestBatchRemove(std::vector<Quest> * QuestList) {
    bool returnRes = true;
    std::vector<Quest>& questRefs = *QuestList;
    for(size_t i=0;i<QuestList->size();i++) {
        if(!QuestRemove(questRefs[i]))
            returnRes = false;
    }
    return returnRes;
}

bool DB::Manager::ReplaceReferences(Quest * NewReference, std::vector<Quest> * QuestList){
    std::vector<Quest>& questRefs = *QuestList;
    bool returnRes = true;
    for(size_t i=0;i<QuestList->size();i++) {
        try {
            *Utils::session << "UPDATE Quest SET ParentId='"+NewReference->Id.toString()+"' WHERE Id='"+questRefs[i].Id.toString()+"';", now;
        }catch(Poco::Exception ex) {
            std::cout << ex.displayText() << std::endl;
            returnRes = false;
        }
    }
    return returnRes;
}

void DB::Manager::RetrieveAllWorlds(std::vector<World> * list) {
    Statement select(*Utils::session);
    std::vector<QType::TempWorld> worlds;

    select << "SELECT * FROM World;",
    into(worlds);


    while (!select.done())
    {
        select.execute();
        for(size_t i=0;i<worlds.size();i++) {
            list->push_back(World(worlds[i]));
        }
    }
}
