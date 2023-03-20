#include "Utility.h"

std::vector<std::string> Utility::split(std::string string, std::string delim) {
    int start = 0;
    int end = 0;
    int length = delim.length();
    std::string buf;
    std::vector<std::string> entries;

    // Until no further occurance of delimiter
    while ((end = string.find(delim, start)) != -1) {
        // Split off entry from current start pos to pos of delimiter
        buf = string.substr(start, end - start);
        // Update new start pos
        start = end + length;
        // Store entry
        entries.push_back(buf);
    }

    entries.push_back(string.substr(start));

    // Return all found entries
    return entries;
}

std::string Utility::getInput(std::string prompt) {
    std::cout << prompt << std::endl;

    std::string input;
    std::cin >> input;

    return input;
}

// Returns index to given loop count i and start index; -1 if max count has been
int Utility::quadraticProbing(int i, int index) {
    // If table length has been reached, do not continue
    if (i > TABLE_LENGTH) return -1;

    // Every offset twice with alternating signs
    int in = std::floor(i / 2);
    int jump = (int) std::pow(in, 2);
    jump = (i % 2 == 0) ? jump : -jump;

    // Jump to new position, take absolute value of it and mod to fit into table
    index += jump;
    index = std::abs(index);
    index %= TABLE_LENGTH;

    return index;
}