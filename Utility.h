#ifndef UE1_UTILITY_H
#define UE1_UTILITY_H

#include <vector>
#include <string>
#include <cstdarg>
#include <iostream>
#include <cmath>

namespace Utility {
    std::vector<std::string> split(std::string string, std::string delim);
    
    const int PLOT_WIDTH = 30;
    const int PLOT_HEIGHT = 20;

    const char Y_AXIS_LINE = char(179);
    const char X_AXIS_LINE = char(196);
    const char Y_AXIS_ARROW = char(94);
    const char X_AXIS_ARROW = char(62);

    const char BOTTOMLEFTCORNER = char(192);

    const std::string MARGIN = "       ";

    const int TABLE_LENGTH = 211;
    std::string getInput(std::string prompt);
    int quadraticProbing(int i, int index);
};


#endif