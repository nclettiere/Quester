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
    std::tuple<Poco::File, bool> t = GetFileFrom ( DefaultWorldsPath );
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
            for ( Poco::JSON::Array::ConstIterator it= arr->begin(); it != arr->end(); ++it ) {
                Poco::JSON::Object::Ptr object = arr->getObject ( i );
                WorldList[i] = wxString ( object->getValue<std::string> ( "name" ) );
                i++;
            }
        } catch ( Poco::Exception ex ) {
            cout << ex.displayText() << endl;
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
