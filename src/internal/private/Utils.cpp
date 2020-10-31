#include "../public/Utils.h"

Utils::Utils()
{
}

bool Utils::GenerateCache()
{
    std::cout << "Looking for: " << Utils::GetCacheFilePath() << std::endl;
    
    Poco::File FileCache(Utils::GetCacheFilePath());
    
    if (!FileCache.exists()) {
        // file does not exist 

        try {
            FileCache.createFile();
        }
        catch (Poco::FileException ex) {
            cout << ex.displayText() << endl;
        }

        cout << "File created" << endl;

        return true;
    }

    cout << "File already exist" << endl;
    
    return false;
}

std::string Utils::GetCacheFilePath()
{

    Poco::Path configFile = Poco::Path(Poco::Path::configHome()).append(Poco::Path("Quester/.generated"));

    try {
        //ensures directory exist
        Poco::File(Poco::Path(Poco::Path::configHome()).append(Poco::Path("Quester/"))).createDirectory();
    }
    catch (Poco::FileException ex) {
        cout << ex.displayText() << endl;
    }


    return configFile.toString();
}

void Utils::OpenConsole()
{
    int outHandle, errHandle, inHandle;
    FILE* outFile, * errFile, * inFile;
    AllocConsole();
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = 9999;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    outHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    errHandle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
    inHandle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);

    outFile = _fdopen(outHandle, "w");
    errFile = _fdopen(errHandle, "w");
    inFile = _fdopen(inHandle, "r");

    *stdout = *outFile;
    *stderr = *errFile;
    *stdin = *inFile;

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    std::ios::sync_with_stdio();

    freopen("CONOUT$", "w", stdout);

}