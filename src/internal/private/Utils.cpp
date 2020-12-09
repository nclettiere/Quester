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
    Poco::Path DefaultWorldsPath = Poco::Path ( Context )
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
    Poco::Path DBStructurePath = Poco::Path ( Context )
        .append ( "/Public/Default/CreateStructure.db" );
    
    std::string buffer;
    std::string DBString;

    try {
        Poco::FileInputStream fis ( DBStructurePath.toString(), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            DBString += buffer;
        }
        fis.close();
    }catch( Poco::Exception ex ) {
        cout << ex.displayText() << endl;
    }
    
    return DBString;
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
