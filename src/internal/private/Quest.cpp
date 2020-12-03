#include <public/Quest.h>

Quest::Quest() {}

Quest::Quest (
    Poco::UUID Id,
    std::string Name, 
		std::string WorldName,
		Poco::UUID ParentId,
		std::string ParentQuestName, 
		bool IsMain, 
		bool IsFailable, 
		bool IsOptional) {
    Quest::Id = Id;
    Quest::Name = Name;
    Quest::IsMain = IsMain;
    Quest::WorldName = WorldName;
    Quest::ParentId = ParentId;
    Quest::ParentQuestName = ParentQuestName;
    Quest::IsFailable = IsFailable;
    Quest::IsOptional = IsOptional;
}

Quest::Quest(QType::TempQuest tmpQuest) {
    try {
        Poco::UUID uuid;
        bool idValid = uuid.tryParse(tmpQuest.get<0>());
        bool parentIdValid = uuid.tryParse(tmpQuest.get<6>());
        if(idValid) {
            Quest::Id = Poco::UUID(tmpQuest.get<0>());
        }else {
            Quest::Id = Poco::UUID();
        }
        Quest::Name = tmpQuest.get<1>();
        Quest::WorldName = tmpQuest.get<2>();
        Quest::IsMain = tmpQuest.get<3>();
        Quest::IsFailable = tmpQuest.get<4>();
        Quest::IsOptional = tmpQuest.get<5>();
        if(parentIdValid) {
            Quest::ParentId = Poco::UUID(tmpQuest.get<6>());
        }else {
            Quest::ParentId = Poco::UUID();
        }
    }catch( Poco::Exception ex) {
        std::cout << ex.displayText();
    }
}

Quest Quest::From(QType::TempQuest tmpQuest) {
    Quest q;
    try {
       Poco::UUID uuid;
       bool idValid = uuid.tryParse(((std::string)tmpQuest.get<0>()));
       if(idValid) {
           q.Id = Poco::UUID(tmpQuest.get<0>());
       }else {
           std::cout << "\tRETURNING DEFAULT\n";
           return Quest();
       }
        q.Name = (std::string) tmpQuest.get<1>();
        q.WorldName = (std::string) tmpQuest.get<2>();
        q.IsMain = (bool) tmpQuest.get<3>();
        q.IsFailable = (bool) tmpQuest.get<4>();
        q.IsOptional = (bool) tmpQuest.get<5>();
        bool parentIdValid = uuid.tryParse(tmpQuest.get<6>());
        if(parentIdValid) {
            q.ParentId = Poco::UUID(tmpQuest.get<6>());
        }else {
            q.ParentId = Poco::UUID();
        }
    }catch( Poco::Exception ex) {
        std::cout << ex.displayText();
    }

    return q;
}

void Quest::UpdateParent() {
    ParentId = Poco::UUID();
}
void Quest::UpdateParent(Poco::UUID Id) {
    ParentId = Id;
}
void Quest::UpdateParent(Quest * Quest) {
    ParentId = Quest->Id;
}

const char* Quest::GetName() {
	return this->Name.c_str();
}

bool Quest::operator!=(Quest const &obj) {
	return (this->Id != obj.Id);
}