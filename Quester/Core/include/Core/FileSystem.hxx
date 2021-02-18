//
// Created by Percebe64 on 2/17/2021.
//

#ifndef QUESTER_FILESYSTEM_HXX
#define QUESTER_FILESYSTEM_HXX

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

class FileSystem {
public:
    FileSystem() = default;

    static char* ReadFile(const char *filename);
    static bool WriteFile(const char *filename, char* data);

};

#endif //QUESTER_FILESYSTEM_HXX
