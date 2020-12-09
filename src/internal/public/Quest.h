#pragma once

#include <public/Globals.h>

#include <iostream>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/Exception.h>
#include <Poco/Tuple.h>

class Quest
{
public:
    Poco::UUID Id;
	std::string Name;
	bool IsMain;
    Poco::UUID WorldId;
	Poco::UUID ParentId;
	std::string ParentQuestName;
	bool IsFailable;
	bool IsOptional;

public:
    Quest() {
        Poco::UUIDGenerator generator = Poco::UUIDGenerator();
        this->Id = generator.create();
    };

    Quest (
        Poco::UUID Id,
        std::string Name,
        Poco::UUID WorldId,
        Poco::UUID ParentId,
        std::string ParentQuestName,
        bool IsMain,
        bool IsFailable,
        bool IsOptional) {
        this->Id = Id;
        this->Name = Name;
        this->IsMain = IsMain;
        this->WorldId = WorldId;
        this->ParentId = ParentId;
        this->ParentQuestName = ParentQuestName;
        this->IsFailable = IsFailable;
        this->IsOptional = IsOptional;
    };

    Quest(QType::TempQuest tmpQuest) {
        try {
            Poco::UUID uuid;
            bool idValid = uuid.tryParse(tmpQuest.get<0>());
            bool worldIdValid = uuid.tryParse(tmpQuest.get<2>());
            bool parentIdValid = uuid.tryParse(tmpQuest.get<6>());
            if(idValid) {
                this->Id = Poco::UUID(tmpQuest.get<0>());
            }else {
                this->Id = Poco::UUID();
            }
            this->Name = tmpQuest.get<1>();
            if(parentIdValid) {
                this->WorldId = Poco::UUID(tmpQuest.get<2>());
            }else {
               this->WorldId = Poco::UUID();
            }
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
