#pragma once

#include <public/Globals.h>

#include <iostream>
#include <Poco/UUID.h>
#include <Poco/Exception.h>
#include <Poco/Tuple.h>

class Quest
{
public:
    Poco::UUID Id;
	std::string Name;
	bool IsMain;
	std::string WorldName;
	Poco::UUID ParentId;
	std::string ParentQuestName;
	bool IsFailable;
	bool IsOptional;

public:
    Quest() {};

    Quest (
        Poco::UUID Id,
        std::string Name,
        std::string WorldName,
        Poco::UUID ParentId,
        std::string ParentQuestName,
        bool IsMain,
        bool IsFailable,
        bool IsOptional) {
        this->Id = Id;
        this->Name = Name;
        this->IsMain = IsMain;
        this->WorldName = WorldName;
        this->ParentId = ParentId;
        this->ParentQuestName = ParentQuestName;
        this->IsFailable = IsFailable;
        this->IsOptional = IsOptional;
    };

    Quest(QType::TempQuest tmpQuest) {
        try {
            Poco::UUID uuid;
            bool idValid = uuid.tryParse(tmpQuest.get<0>());
            bool parentIdValid = uuid.tryParse(tmpQuest.get<6>());
            if(idValid) {
                this->Id = Poco::UUID(tmpQuest.get<0>());
            }else {
                this->Id = Poco::UUID();
            }
            this->Name = tmpQuest.get<1>();
            this->WorldName = tmpQuest.get<2>();
            this->IsMain = tmpQuest.get<3>();
            this->IsFailable = tmpQuest.get<4>();
            this->IsOptional = tmpQuest.get<5>();
            if(parentIdValid) {
                this->ParentId = Poco::UUID(tmpQuest.get<6>());
            }else {
                this->ParentId = Poco::UUID();
            }
        }catch( Poco::Exception ex) {
            std::cout << ex.displayText();
        }
    }

    static Quest From(QType::TempQuest tmpQuest);
	const char* GetName();
	void UpdateParent(); // Set to NULL
	void UpdateParent(Poco::UUID Id);
	void UpdateParent(Quest * Quest);

	bool operator!=(Quest const &obj);
};
