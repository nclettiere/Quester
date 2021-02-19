//
// Created by Percebe32 on 2/18/2021.
//

#ifndef QUESTER_QGLOBALS_HXX
#define QUESTER_QGLOBALS_HXX

static void GenerateUUID(Poco::UUID& uuidObj) {
    auto uuidGenerator = Poco::UUIDGenerator();
    uuidObj = uuidGenerator.create();
}

struct CharacterStats {
    CharacterStats() {}
};

struct DialogueOption {
    DialogueOption() {}
};

#endif //QUESTER_QGLOBALS_HXX
