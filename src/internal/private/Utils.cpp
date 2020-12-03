#include "../public/Utils.h"

bool Utils::GenerateCache() {
    Poco::File FileCache ( Utils::GetCacheFilePath() );

    cout << "Inspecting integrity of local files..." << endl;
    Utils::GenerateStructure();

    if ( !FileCache.exists() ) {
        // file does not exist
        try {
            FileCache.createFile();
        } catch ( Poco::FileException ex ) {
            return false;
        }

        return true;
    }
    return false;
}

std::string Utils::GetCacheFilePath() {

    Poco::Path configFile = Poco::Path ( Poco::Path::configHome() ).append ( Poco::Path ( "Quester/.generated" ) );

    try {
        //ensures directory exist
        Poco::File ( Poco::Path ( Poco::Path::configHome() ).append ( Poco::Path ( "Quester/" ) ) ).createDirectory();
    } catch ( Poco::FileException ex ) {
        cout << ex.displayText() << endl;
    }


    return configFile.toString();
}

void Utils::GenerateStructure() {
    Poco::Path QuestFolderPath = Poco::Path ( Poco::Path::dataHome() ).append ( Poco::Path ( "Quester/Quests/" ) );
    Poco::Path QuestMainFilePath = Poco::Path ( Utils::GetEssentialFile ( FileKind::Quests ) );
    Poco::File QuestFolder = Poco::File ( QuestFolderPath );
    Poco::File QuestDefaultFile = Poco::File ( QuestMainFilePath );

    cout << "QuestFolder found: " << QuestFolder.exists() << endl;
    cout << "QuestDefaultFile found: " << QuestDefaultFile.exists() << endl;

    if (!QuestFolder.exists()) {
        cout << "Creating: " << QuestFolderPath.toString() << endl;
        QuestFolder.createDirectories();
    }
    
    if ( !QuestDefaultFile.exists() ) {
        try {
            cout << "Creating: " << QuestMainFilePath.toString() << endl;
            if (QuestDefaultFile.createFile()) {

                Poco::Dynamic::Var Dynamic("[]");

                Poco::FileOutputStream fout(Utils::GetEssentialFile(FileKind::Quests));
                Poco::JSON::Stringifier::stringify(Dynamic, fout, 1, 1, Poco::JSON_ESCAPE_UNICODE);
                fout.close();
            }
            else {
                //wxLogMessage("Couldnt create %s", Utils::GetEssentialFile(FileKind::Quests));
            }
        }catch(Poco::Exception ex) {
            cout << ex.displayText() << endl;
        }
    }

}

std::string Utils::GetEssentialFile ( FileKind Kind ) {
    Poco::Path QuesterDataPath = Poco::Path ( Poco::Path::dataHome() );

    switch ( Kind ) {
    case FileKind::Cache:
        return Utils::GetCacheFilePath();
        break;
    case FileKind::Quests:
        return QuesterDataPath.append ( Poco::Path ( "Quester/Quests/Base.json" ) ).toString();
        break;
    case FileKind::DefaultWorlds:
        return Poco::Path::current();
        break;
    case FileKind::Swap:
        return "";
        break;
    }

    return "";
}

std::vector<std::string> Utils::GetDefaultWorldsAsList ( ) {
    Poco::Path DefaultWorldsPath = Poco::Path ( GetExecutablePath().toString() )
        .parent()
        .append ( "/Public/Default/Worlds.json" );
    std::vector<std::string> WorldList;

    // if file exists
    try {
        string buffer;
        string JSONString;

        Poco::FileInputStream fis ( DefaultWorldsPath.toString(), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            JSONString += buffer + '\n';
        }
        fis.close();

        try {
            // Parse JSON String
            Poco::JSON::Parser Parser;
            Poco::Dynamic::Var result = Parser.parse ( JSONString );
            Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();

            uint8_t i;
            for ( i = 0; i < arr->size(); i++ ) {
                try {
                    cout << i << endl;
                    Poco::JSON::Object::Ptr object = arr->getObject ( i );
                    WorldList.push_back ( std::string (object->getValue<std::string> ( "name" ))  );
                    //WorldList[i] = std::string ( );
                } catch ( Poco::NotFoundException ex ) {
                    cout << "3 " << ex.displayText() << endl;
                }
            }
        } catch ( Poco::NotFoundException ex ) {
            cout << "2 " << ex.displayText() << endl;
        }

    } catch ( Poco::FileNotFoundException ex ) {
        cout << ex.displayText() << endl;
    }

    return WorldList;
}

std::vector<Quest*> Utils::GetQuestsAsList() {
    Poco::Path QuestsListPath = Poco::Path ( Utils::GetEssentialFile ( FileKind::Quests ) );

    std::vector<Quest*> QuestList;

    // if file exists
    try {
        string buffer;
        string JSONString;

        Poco::FileInputStream fis ( QuestsListPath.toString(), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            JSONString += buffer + '\n';
        }
        fis.close();

        try {
            // Parse JSON String
            Poco::JSON::Parser Parser;
            Poco::Dynamic::Var result = Parser.parse ( JSONString );
            Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();

            uint8_t i;
            for ( i = 0; i < arr->size(); i++ ) {
                try {
                    Poco::JSON::Object::Ptr object = arr->getObject ( i );

                    Quest * quest = new Quest();
                    quest->Id = Poco::UUID ( object->getValue<std::string> ( "ID" ) );
                    quest->Name = object->getValue<std::string> ( "Name" );
                    //quest->WorldId = object->getValue<Poco::UUID> ( "WorldId" );
                    quest->WorldName = object->getValue<std::string> ( "WorldName" );
                    
                    try {
                        quest->ParentId = Poco::UUID ( object->getValue<std::string> ( "ParentId" ) );
                    }catch( Poco::Exception ex) {
                        quest->ParentId = Poco::UUID ();
                    }

                    quest->ParentQuestName = object->getValue<std::string> ( "ParentQuestName" );
                    quest->IsFailable = object->getValue<bool> ( "IsFailable" );
                    quest->IsOptional = object->getValue<bool> ( "IsOptional" );

                    QuestList.push_back ( quest );
                } catch ( Poco::Exception ex ) {
                    cout << "3 " << ex.message() << endl;
                }
            }
        } catch ( Poco::Exception ex ) {
            cout << "2 " << ex.displayText() << endl;
        }

    } catch ( Poco::FileNotFoundException ex ) {
        cout << ex.displayText() << endl;
    }

    return QuestList;
}

std::vector<Quest*> Utils::GetQuestsAsList(Poco::JSON::Array::Ptr Quests)
{
    std::vector<Quest*> QuestList;

    for (int i = 0; i < Quests->size(); i++) {
        try {
            cout << i << endl;
            Poco::JSON::Object::Ptr object = Quests->getObject(i);

            Quest* quest = new Quest();
            quest->Id = Poco::UUID(object->getValue<std::string>("ID"));
            quest->Name = object->getValue<std::string>("Name");
            //quest->WorldId = Poco::UUID(object->getValue<std::string>("WorldId"));
            quest->WorldName = object->getValue<std::string>("WorldName");
            quest->ParentId = Poco::UUID(object->getValue<std::string>("ParentId"));
            quest->ParentQuestName = object->getValue<std::string>("ParentQuestName");
            quest->IsFailable = object->getValue<bool>("IsFailable");
            quest->IsOptional = object->getValue<bool>("IsOptional");

            QuestList.push_back(quest);
        }
        catch (Poco::Exception ex) {
            cout << "Utils::GetQuestsAsList(Poco::JSON::Array::Ptr Quests) " << ex.displayText() << endl;
        }
    }

    return QuestList;
}

Quest* Utils::GetQuestWithId ( Poco::UUID id ) {
    std::vector<Quest*> QuestsList = GetQuestsAsList();

    for (std::size_t i = 0; i != QuestsList.size(); ++i) {
        if(QuestsList[i]->Id == id) { return QuestsList[i]; }
    }

    // On fail
    return nullptr;
}

Quest* Utils::GetQuestWithId ( Poco::UUID id, std::vector<Quest*> QuestsList ) {
    for (std::size_t i = 0; i != QuestsList.size(); ++i) {
        if(QuestsList[i]->Id == id) { return QuestsList[i]; }
    }

    // On fail
    return nullptr;
}

std::vector<Quest*> Utils::GetQuestWithId ( std::vector<Poco::UUID> QuestsList ) {

    std::vector<Quest*> ResultList;

    for (std::size_t i = 0; i != QuestsList.size(); ++i) {
        try {
            Quest * q = GetQuestWithId(QuestsList[i]);
            if(q != nullptr)
                ResultList.push_back(q);
        }catch( Poco::Exception ex ) {
        }
    }

    // On fail
    return ResultList;
}

//bool Utils::RemoveQuest(Poco::UUID Id) {
//    Poco::JSON::Array::Ptr QuestList = Utils::GetQuestAsJSON();
//
//    for (int i = 0; i < QuestList->size(); i++) {
//        Poco::JSON::Object::Ptr object = QuestList->getObject(i);
//        Poco::UUID ObjectId = Poco::UUID(object->getValue<std::string>("ID"));
//
//        if (Id == ObjectId) {
//            QuestList->remove(i);
//            break;
//        }
//    }
//
//    Poco::Dynamic::Var Dynamic(QuestList);
//
//    try {
//        Poco::FileOutputStream fout(Utils::GetEssentialFile(FileKind::Quests));
//        Poco::JSON::Stringifier::stringify(Dynamic, fout, 1, 1, Poco::JSON_ESCAPE_UNICODE);
//        fout.close();
//        return true;
//    }
//    catch (Poco::Exception ex) {
//        cout << "Utils::RemoveQuest(Poco::UUID Id) " << ex.displayText() << endl;
//        return false;
//    }
//}

std::tuple<bool, std::string> Utils::CreateNewQuest ( Quest* QuestData ) {
    Poco::JSON::Object::Ptr JSONDataQuest = new Poco::JSON::Object;
    JSONDataQuest->set ( "ID", QuestData->Id.toString() );
    JSONDataQuest->set ( "Name", QuestData->Name );
    // TODO => JSONDataQuest->set ( "WorldId", QuestData->WorldId );
    JSONDataQuest->set ( "WorldName", QuestData->WorldName );
    JSONDataQuest->set ( "ParentId", QuestData->ParentId.toString() );
    JSONDataQuest->set ( "ParentQuestName", QuestData->ParentQuestName );
    JSONDataQuest->set ( "IsMain", QuestData->IsMain );
    JSONDataQuest->set ( "IsFailable", QuestData->IsFailable );
    JSONDataQuest->set ( "IsOptional", QuestData->IsOptional );

    Poco::JSON::Array::Ptr QuestList = Utils::GetQuestAsJSON();

    QuestList->add ( JSONDataQuest );

    Poco::Dynamic::Var Dynamic ( QuestList );

    try {
        Poco::FileOutputStream fout ( Utils::GetEssentialFile ( FileKind::Quests ) );
        Poco::JSON::Stringifier::stringify ( Dynamic, fout, 1, 1, Poco::JSON_ESCAPE_UNICODE );
        fout.close();
        return std::tuple<bool, std::string> {true, "Success" };
    } catch ( Poco::Exception ex ) {
        return std::tuple<bool, std::string> {false, ex.displayText() };
    }
}

Poco::JSON::Array::Ptr Utils::GetQuestAsJSON() {
    std::tuple<Poco::File, bool> ResultFile = Utils::GetFileFrom ( Utils::GetEssentialFile ( FileKind::Quests ) );

    // if file exists
    if ( std::get<bool> ( ResultFile ) ) {
        string buffer;
        string JSONString;
        try {
            Poco::FileInputStream fis ( GetEssentialFile ( FileKind::Quests ) );
            while ( getline ( fis, buffer ) ) {
                JSONString += buffer + '\n';
            }
            fis.close();
        } catch ( Poco::Exception ex ) {
            cout << "&alpha " << ex.displayText() << endl;
        }

        try {
            if ( JSONString.size() == 0 ) {
                cout << "0 size" << endl;
                return Poco::JSON::Array::Ptr();
            }
            Poco::JSON::Parser Parser;
            Poco::Dynamic::Var result = Parser.parse ( JSONString );
            return result.extract<Poco::JSON::Array::Ptr>();
        } catch ( Poco::Exception ex ) {
            cout << "1 " << ex.displayText() << endl;
            return nullptr;
        }
    }

    return nullptr;
}

std::tuple<Poco::File, bool> Utils::GetFileFrom ( std::string FilePath ) {
    Poco::File f ( FilePath );
    return std::tuple<Poco::File, bool> {f, f.exists() };
}

std::tuple<Poco::File, bool> Utils::GetFileFrom ( Poco::File FilePath ) {
    Poco::File f ( FilePath );
    return std::tuple<Poco::File, bool> {f, f.exists() };
}

std::string Utils::GetValue ( Poco::JSON::Object::Ptr JSONObject, const char *Key ) {
    Poco::Dynamic::Var Variable;
    string ReturnString;
    string lsKey ( Key );
    Variable = JSONObject->get ( Key );
    ReturnString = Variable.convert<std::string>();

    return ReturnString;
}

std::string Utils::GetDBStructure() {
    Poco::Path DBStructurePath = Poco::Path ( GetExecutablePath().toString() )
        .parent()
        .append ( "/Public/Default/CreateStructure.db" );
    
    std::string buffer;
    std::string DBString;

    try {
        Poco::FileInputStream fis ( DBStructurePath.toString(), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            DBString += buffer + '\n';
        }
        fis.close();
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
    
    return DBString;
}

Poco::Path Utils::GetExecutablePath() {
    try {
#ifdef _WIN32
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return Poco::Path(path);
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return Poco::Path(std::string(result, (count > 0) ? count : 0));
#endif
    }catch(Poco::NotFoundException ex) {
        cout << ex.displayText();
    }
}

// Windows Only
void Utils::OpenConsole() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    int outHandle, errHandle, inHandle;
    FILE* outFile, * errFile, * inFile;
    AllocConsole();
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo ( GetStdHandle ( STD_OUTPUT_HANDLE ), &coninfo );
    coninfo.dwSize.Y = 9999;
    SetConsoleScreenBufferSize ( GetStdHandle ( STD_OUTPUT_HANDLE ), coninfo.dwSize );

    outHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_OUTPUT_HANDLE ), _O_TEXT );
    errHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_ERROR_HANDLE ), _O_TEXT );
    inHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_INPUT_HANDLE ), _O_TEXT );

    outFile = _fdopen ( outHandle, "w" );
    errFile = _fdopen ( errHandle, "w" );
    inFile = _fdopen ( inHandle, "r" );

    *stdout = *outFile;
    *stderr = *errFile;
    *stdin = *inFile;

    setvbuf ( stdout, NULL, _IONBF, 0 );
    setvbuf ( stderr, NULL, _IONBF, 0 );
    setvbuf ( stdin, NULL, _IONBF, 0 );

    std::ios::sync_with_stdio();

    freopen ( "CONOUT$", "w", stdout );
#endif
}
