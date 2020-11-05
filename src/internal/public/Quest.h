#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/dataview.h>

#include <iostream>

class Quest
{
public:
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
	Quest(std::string Name, 
		int World, 
		std::string WorldName, 
		int ParentQuest, 
		std::string ParentQuestName, 
		bool IsMain, 
		bool IsFailable, 
		bool IsOptional);

};

