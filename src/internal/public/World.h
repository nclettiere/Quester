#pragma once

#include <public/Globals.h>

#include <iostream>
#include <string>

#include <Poco/UUID.h>
#include <Poco/Exception.h>
#include <Poco/Tuple.h>

class World
{
public:
    Poco::UUID Id;
    std::string Name;
    std::string Description;
public:
    World() {};
    World(Poco::UUID Id,
        std::string Name,
        std::string Description) {
        this->Id = Id;
        this->Name = Name;
        this->Description = Description;
    };

    World(QType::TempWorld tmpWorld) {
        try {
            Poco::UUID uuid;
            bool idValid = uuid.tryParse(tmpWorld.get<0>());
            if(idValid) {
                this->Id = Poco::UUID(tmpWorld.get<0>());
            }else {
                this->Id = Poco::UUID();
            }
            this->Name = tmpWorld.get<1>();
            this->Description = tmpWorld.get<2>();
        }catch( Poco::Exception ex) {
            std::cout << ex.displayText();
        }
    };

    static World From(QType::TempWorld tmpWorld);
	const char* GetName();
    //void UpdateParent(); // Set to NULL
    //void UpdateParent(Poco::UUID Id);
    //void UpdateParent(Quest * Quest);

    bool operator!=(World const &obj);
};
