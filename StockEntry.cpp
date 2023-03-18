#include <iostream>
#include "StockEntry.h"

StockEntry::StockEntry(std::string line) {
    std::vector<std::string> tokens = Utility::split(line, ",");

    this->date = std::move(tokens.at(0));
    this->open = std::stof(tokens.at(1));
    this->high = std::stof(tokens.at(2));
    this->low = std::stof(tokens.at(3));
    this->close = std::stof(tokens.at(4));
    this->adjClose = std::stof(tokens.at(5));
    this->volume = std::stol(tokens.at(6));
}

std::ostream &operator<<(std::ostream &os, const StockEntry &entry) {
    os << "date: " << entry.date << " open: " << entry.open << " high: " << entry.high << " low: " << entry.low
       << " close: " << entry.close << " volume: " << entry.volume << " adjClose: " << entry.adjClose;
    return os;
}

void StockEntry::printToFile(std::ofstream &file) {
    file << this->date << "," << this->open << "," << this->high << "," << this->low << "," << this->close << "," << this->adjClose << "," << this->volume;
}
