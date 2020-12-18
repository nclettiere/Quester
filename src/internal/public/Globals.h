#pragma once
#include <iostream>
#include <Poco/Tuple.h>

namespace QType
{
    enum class Localization { ES, EN, IT };

    typedef Poco::Tuple<std::string, std::string, std::string, int, int, int, std::string> TempQuest;
    typedef Poco::Tuple<std::string, std::string, std::string> TempWorld;
    typedef Poco::Tuple<std::string, Localization> DialogueTemplate;
    //const unsigned int g_nMyGlobalType = 10;
    // etc.
}
