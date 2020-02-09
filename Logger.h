//
// Created by gilaad on 2/2/20.
//

#ifndef SCRATCH3D_LOGGER_H
#define SCRATCH3D_LOGGER_H


#include <string>

class Logger {
    static bool loggedYet;

public:
    static void LogToFile(const std::string& logMsg);
};


#endif //SCRATCH3D_LOGGER_H
