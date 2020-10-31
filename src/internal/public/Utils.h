#pragma once

#include <string>
#include <iostream>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Exception.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <fstream>
#include <fcntl.h>
#include <corecrt_io.h>
#endif

using namespace std;

enum class FileKind { Cache, Quests, Swap };

class Utils
{
public:
    Utils();
    ~Utils();
    
    static string GetCacheFilePath();
    static bool GenerateCache();
    
    static string GetEssentialFile(FileKind Kind);
    
    // Windows Only
    static void OpenConsole();
    
protected:
    static void GenerateStructure();
};
