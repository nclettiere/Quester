#include <public/Quest.h>

Quest Quest::From(QType::TempQuest tmpQuest) {
    Quest q;
    try {
       Poco::UUID uuid;
       bool idValid = uuid.tryParse(((std::string)tmpQuest.get<0>()));
       bool worldIdValid = uuid.tryParse(((std::string)tmpQuest.get<2>()));
       if(idValid) {
           q.Id = Poco::UUID(tmpQuest.get<0>());
       }else {
           std::cout << "\tRETURNING DEFAULT\n";
           return Quest();
       }
        q.Name = (std::string) tmpQuest.get<1>();
        if(worldIdValid) {
            q.WorldId = Poco::UUID(tmpQuest.get<2>());
        }else {
            q.WorldId = Poco::UUID();
        }
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
