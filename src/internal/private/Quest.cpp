#include "../public/Quest.h"

Quest::Quest() {
}

Quest::Quest (
        Poco::UUID Id,
        std::string Name, 
		int World, 
		std::string WorldName, 
		int ParentQuest, 
		std::string ParentQuestName, 
		bool IsMain, 
		bool IsFailable, 
		bool IsOptional) {
    Quest::Id              = Id;
    Quest::Name            = Name;
    Quest::IsMain          = IsMain;
    Quest::World           = World;
    Quest::WorldName       = WorldName;
    Quest::ParentQuest     = ParentQuest;
    Quest::ParentQuestName = ParentQuestName;
    Quest::IsFailable      = IsFailable;
    Quest::IsOptional      = IsOptional;
}
