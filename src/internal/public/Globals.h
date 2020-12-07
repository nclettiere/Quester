#pragma once
#include <iostream>
#include <Poco/Tuple.h>

namespace QType
{
    typedef Poco::Tuple<std::string, std::string, std::string, int, int, int, std::string> TempQuest;
    typedef Poco::Tuple<std::string, std::string, std::string> TempWorld;
    //const unsigned int g_nMyGlobalType = 10;
    // etc.
}
