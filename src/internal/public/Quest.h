#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/dataview.h>

#include <iostream>
#include <Poco/UUID.h>

class Quest
{
public:
    Poco::UUID Id;
	std::string Name;
	bool IsMain;
	int World;
	std::string WorldName;
	int ParentQuest;
	std::string ParentQuestName;
	bool IsFailable;
	bool IsOptional;

public:
	Quest();
	Quest(
        Poco::UUID Id,
        std::string Name, 
		int World, 
		std::string WorldName, 
		int ParentQuest, 
		std::string ParentQuestName, 
		bool IsMain, 
		bool IsFailable, 
		bool IsOptional);

};

