#include "../public/Utils.h"

bool Utils::GenerateCache() {
    std::cout << "Looking for: " << Utils::GetCacheFilePath() << std::endl;

    Poco::File FileCache ( Utils::GetCacheFilePath() );

    Utils::GenerateStructure();

    if ( !FileCache.exists() ) {
        // file does not exist

        try {
            FileCache.createFile();
        } catch ( Poco::FileException ex ) {
            cout << ex.displayText() << endl;
        }

        cout << "Generating Structure" << endl;

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

    Poco::Path QuestMainFilePath = Poco::Path ( Poco::Path::dataHome() ).append ( Poco::Path ( "Quester/Quests/Base.json" ) );

    auto QuestFolder = Poco::File ( QuestFolderPath );
    auto QuestDefaultFile = Poco::File ( QuestMainFilePath );
    if ( !QuestFolder.exists() ) {
        try {
            //ensures directory exist
            QuestFolder.createDirectories();
        } catch ( Poco::FileException ex ) {
            cout << ex.displayText() << endl;
        }
    }

    if ( !QuestDefaultFile.exists() ) {
        try {
            cout << "Creating..." << QuestMainFilePath.toString() << "\n";
            QuestDefaultFile.createFile();

            // Write default json value
            Poco::FileOutputStream fout ( QuestMainFilePath.toString(), std::ios::out );
            fout << "[]";
            fout.close();
        } catch ( Poco::FileException ex ) {
            cout << ex.displayText() << endl;
        }
    }

    cout << "Created Path: " << QuestMainFilePath.toString() << endl;
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

wxString * Utils::GetDefaultWorldsAsList ( std::string Context ) {
    Poco::Path DefaultWorldsPath = Poco::Path ( Context )
                                   .parent()
                                   .append ( "/Public/Default/Worlds.json" );

    cout << "DefaultWorldsPath: " << DefaultWorldsPath.toString() << endl;

    wxString * WorldList;

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

            WorldList = new wxString[arr->size()];

            uint8_t i;
            for (i = 0; i < arr->size(); i++) {
                try {
                    cout << i << endl;
                    Poco::JSON::Object::Ptr object = arr->getObject ( i );
                    WorldList[i] = wxString ( object->getValue<std::string> ( "name" ) );
                }
                catch (Poco::Exception ex) {
                    cout << "3 " << ex.message() << endl;
                }
            }
        } catch ( Poco::Exception ex ) {
            cout << "2 " << ex.displayText() << endl;
        }

    } catch ( Poco::FileNotFoundException ex ) {
        cout << ex.displayText() << endl;
    }

    return WorldList;
}

std::tuple<wxString*, int> Utils::GetQuestsAsList() {
    Poco::Path QuestsListPath = Poco::Path(Utils::GetEssentialFile(FileKind::Quests));

    wxString* QuestsList;
    int QuestLength;

    // if file exists
    try {
        string buffer;
        string JSONString;

        Poco::FileInputStream fis(QuestsListPath.toString(), std::ios::out);
        while (getline(fis, buffer)) {
            JSONString += buffer + '\n';
        }
        fis.close();

        try {
            // Parse JSON String
            Poco::JSON::Parser Parser;
            Poco::Dynamic::Var result = Parser.parse(JSONString);
            Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();

            QuestLength = arr->size();
            QuestsList = new wxString[QuestLength];

            uint8_t i;
            for (i = 0; i < arr->size(); i++) {
                try {
                    cout << i << endl;
                    Poco::JSON::Object::Ptr object = arr->getObject(i);
                    QuestsList[i] = wxString(object->getValue<std::string>("Name"));
                }
                catch (Poco::Exception ex) {
                    cout << "3 " << ex.message() << endl;
                }
            }
        }
        catch (Poco::Exception ex) {
            cout << "2 " << ex.displayText() << endl;
        }

    }
    catch (Poco::FileNotFoundException ex) {
        cout << ex.displayText() << endl;
    }

    return std::tuple<wxString*, int> { QuestsList, QuestLength };
}

std::tuple<bool, std::string> Utils::CreateNewQuest ( QuestData * Data ) {
    Poco::JSON::Object::Ptr JSONDataQuest = new Poco::JSON::Object;
    JSONDataQuest->set ( "Name", Data->Name );
    JSONDataQuest->set ( "World", Data->WorldId );
    JSONDataQuest->set ( "ParentQuest", Data->ParentQuest );
    JSONDataQuest->set ( "IsMain", Data->IsMain );
    JSONDataQuest->set ( "IsFailable", Data->IsFailable );
    JSONDataQuest->set ( "IsOptional", Data->IsOptional );
    
    Poco::JSON::Array::Ptr QuestList = Utils::GetQuestAsJSON();

    QuestList->add(JSONDataQuest);
        
    Poco::Dynamic::Var Dynamic ( QuestList );
    Poco::FileOutputStream fout ( Utils::GetEssentialFile ( FileKind::Quests ) );

    try {
        Poco::JSON::Stringifier::stringify ( Dynamic, fout, 1, 1, Poco::JSON_ESCAPE_UNICODE );
        return std::tuple<bool, std::string> {true, "Success" };
    } catch ( Poco::Exception ex ) {
        return std::tuple<bool, std::string> {false, ex.displayText() };
    }
}

Poco::JSON::Array::Ptr Utils::GetQuestAsJSON() {
    std::tuple<Poco::File, bool> ResultFile = Utils::GetFileFrom(Utils::GetEssentialFile(FileKind::Quests));
    
    // if file exists
    if(std::get<bool>(ResultFile)) {
        string buffer;
        string JSONString;

        Poco::FileInputStream fis ( GetEssentialFile(FileKind::Quests), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            JSONString += buffer + '\n';
        }
        fis.close();
        
        try {
            Poco::JSON::Parser Parser;
            Poco::Dynamic::Var result = Parser.parse ( JSONString );
            return result.extract<Poco::JSON::Array::Ptr>();
        }catch(Poco::Exception ex) {
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

    // Get the member Variable
    //
    Variable = JSONObject->get ( Key );

    // Get the Value from the Variable
    //
    ReturnString = Variable.convert<std::string>();

    return ReturnString;
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
