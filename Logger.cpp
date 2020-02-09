//
// Created by gilaad on 2/2/20.
//

#include <fstream>
#include "Logger.h"

bool Logger::loggedYet = false;

void Logger::LogToFile(const std::string& logMsg) {
    if (!loggedYet){
        remove("log.txt");
        loggedYet = true;
    }std::ofstream fStream("log.txt", std::ios_base::app);

    fStream << logMsg << std::endl;
    fStream.close();
}
