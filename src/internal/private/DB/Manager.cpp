#include <public/DB/Manager.h>

void DB::ManagerTest::CreateContext() {
    try {
        // Ensures basic structure of database
        std::cout <<  Utils::GetDBStructure() << std::endl;
        *Utils::session << Utils::GetDBStructure(), now;
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
}

DB::ManagerTest::ManagerTest() {
    try {
        CreateContext();
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
}

bool DB::ManagerTest::InsertQuest(Quest * questData) {
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

Quest  DB::ManagerTest::RetrieveQuest(Poco::UUID id) {
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

std::vector<Quest> DB::ManagerTest::RetrieveQuests(std::vector<Poco::UUID> idList){
    return std::vector<Quest>();
}

void DB::ManagerTest::RetrieveAllQuests(std::vector<Quest> * list) {
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

void DB::ManagerTest::GetRelationships(Poco::UUID Id, std::vector<Quest> * QuestList) {
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

bool DB::ManagerTest::QuestRemove(Quest Quest) {
    try {
        *Utils::session << "DELETE FROM Quest WHERE Id='"+Quest.Id.toString()+"';", now;
    }catch(Poco::Exception ex) {
        std::cout << ex.displayText() << std::endl;
        return false;
    }

    return true;
}
bool DB::ManagerTest::QuestBatchRemove(std::vector<Quest> * QuestList) {
    bool returnRes = true;
    std::vector<Quest>& questRefs = *QuestList;
    for(size_t i=0;i<QuestList->size();i++) {
        if(!QuestRemove(questRefs[i]))
            returnRes = false;
    }
    return returnRes;
}

bool DB::ManagerTest::ReplaceReferences(Quest * NewReference, std::vector<Quest> * QuestList){
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
