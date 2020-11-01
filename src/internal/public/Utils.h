#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Exception.h>
#include <Poco/FileStream.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <fcntl.h>
#include <corecrt_io.h>
#endif

using namespace std;

enum class FileKind { Cache, Quests, DefaultWorlds, Swap };

class Utils
{
public:
    static std::string GetCacheFilePath();
    static bool GenerateCache();
    
    static std::string GetEssentialFile(FileKind Kind);
    static std::tuple<Poco::File, bool> GetFileFrom(std::string FilePath);
    static std::tuple<Poco::File, bool> GetFileFrom(Poco::File FilePath);
    static std::string GetDefaultWorldsAsList(std::string Context);
    
    
    // Windows Only
    static void OpenConsole();
    
protected:
    static void GenerateStructure();
};
