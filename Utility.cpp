#include "Utility.h"

std::vector<std::string> Utility::split(std::string string, std::string delim) {
    int start = 0;
    int end = 0;
    int length = delim.length();
    std::string buf;
    std::vector<std::string> entries;

    while((end = string.find(delim, start)) != -1) {
        buf = string.substr(start, end - start);
        start = end + length;
        entries.push_back(buf);
    }

    entries.push_back(string.substr(start));
    return entries;
}

std::string Utility::getInput(std::string prompt) {
    std::cout << prompt << std::endl;

    std::string input;
    std::cin >> input;

    return input;
}
