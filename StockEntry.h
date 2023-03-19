#ifndef UE1_STOCKENTRY_H
#define UE1_STOCKENTRY_H

#include <ctime>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include "Utility.h"

class StockEntry {
public:
    StockEntry(std::string line);

    void printToFile(std::ofstream &file);
    friend std::ostream &operator<<(std::ostream &os, const StockEntry &entry);

    float getHigh() const;
    float getLow() const;

    float getClose() const;

private:
    std::string date;
    float open;
    float high;
    float low;
    float close;
    long volume;
    float adjClose;
};


#endif
