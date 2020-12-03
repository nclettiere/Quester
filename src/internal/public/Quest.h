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
	Quest();
	Quest(
        Poco::UUID Id,
        std::string Name, 
		std::string WorldName,
		Poco::UUID ParentId,
		std::string ParentQuestName, 
		bool IsMain, 
		bool IsFailable, 
		bool IsOptional);
	Quest(QType::TempQuest tmpQuest);
	static Quest From(QType::TempQuest tmpQuest);
	const char* GetName();
	void UpdateParent(); // Set to NULL
	void UpdateParent(Poco::UUID Id);
	void UpdateParent(Quest * Quest);

	bool operator!=(Quest const &obj);
};