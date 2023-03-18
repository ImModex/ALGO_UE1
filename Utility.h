#ifndef UE1_UTILITY_H
#define UE1_UTILITY_H

#include <vector>
#include <string>
#include <cstdarg>
#include <iostream>

namespace Utility {
    std::vector<std::string> split(std::string string, std::string delim);
    std::string getInput(std::string prompt);
};


#endif