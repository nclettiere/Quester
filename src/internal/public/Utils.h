#pragma once

#include <string>
#include <iostream>
#include <Poco/Path.h>
#include <Poco/File.h>

using namespace std;

class Utils
{
public:
    Utils();
    ~Utils();
    
    static string GetCacheFilePath();
    static bool GenerateCache();
};
