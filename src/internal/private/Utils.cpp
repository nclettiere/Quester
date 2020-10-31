#include "../public/Utils.h"

Utils::Utils()
{
}

bool Utils::GenerateCache()
{
    cout << "Looking for: " << Utils::GetCacheFilePath() << endl;
    
    Poco::File FileCache(Utils::GetCacheFilePath());
    
    if(!FileCache.exists()) {
        // file does not exist 
        cout << "File created" << endl;
        FileCache.createFile();
        
        return true;
    }
    
    cout << "File already exist" << endl;
    
    return false;
}

std::string Utils::GetCacheFilePath()
{
    Poco::Path cacheHome = Poco::Path(Poco::Path::cacheHome());
    cacheHome.append(Poco::Path("Quester/.generated"));
    
    return cacheHome.toString();
}
