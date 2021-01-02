#pragma once
#include <Poco/Tuple.h>
#include <Poco/UUID.h>
#include <QString>

namespace QType
{
    enum class Localization { ES, EN, IT };

    typedef Poco::Tuple<std::string, std::string, std::string, int, int, int, std::string> TempQuest;
    typedef Poco::Tuple<std::string, std::string, std::string> TempWorld;
    typedef Poco::Tuple<std::string, Localization> DialogueTemplate;
    struct DialogueNodeData {
        Poco::UUID Id;
        QString Text;

        bool operator==(const DialogueNodeData& a) const
        {
            return (a.Id == Id);
        }
    };
    //const unsigned int g_nMyGlobalType = 10;
    // etc.
}
