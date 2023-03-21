#ifndef STOCKENTRY_H
#define STOCKENTRY_H

#include <ctime>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include "Utility.h"

// Class that represents one entry of a stock (values of one day)
class StockEntry {
public:
    StockEntry(std::string line);

    // Print to file / ostream
    void printToFile(std::ofstream &file);
    friend std::ostream &operator<<(std::ostream &os, const StockEntry &entry);

    // Get closing value of this entry
    float getClose() const;

private:
    std::string date;
    float open;
    float high;
    float low;
    float close;
    long long int volume;
    float adjClose;
};


#endif
