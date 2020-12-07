#include <public/World.h>

World World::From(QType::TempWorld tmpWorld) {
    World w;
    try {
       Poco::UUID uuid;
       bool idValid = uuid.tryParse(((std::string)tmpWorld.get<0>()));
       if(idValid) {
           w.Id = Poco::UUID(tmpWorld.get<0>());
       }else {
           return World();
       }
        w.Name = (std::string) tmpWorld.get<1>();
        w.Description = (std::string) tmpWorld.get<2>();
    }catch( Poco::Exception ex) {
        std::cout << ex.displayText();
    }

    return w;
}

const char* World::GetName() {
    return this->Name.c_str();
}

bool World::operator!=(World const &obj) {
	return (this->Id != obj.Id);
}
