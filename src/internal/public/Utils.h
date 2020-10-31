#pragma once

#include <fcntl.h>
#include <corecrt_io.h>

#include <string>
#include <iostream>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Exception.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <iostream>
#include <fstream>
#endif

using namespace std;

class Utils
{
public:
    Utils();
    ~Utils();
    
    static string GetCacheFilePath();
    static bool GenerateCache();
    
    static void OpenConsole();
};
