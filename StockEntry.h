#ifndef UE1_STOCKENTRY_H
#define UE1_STOCKENTRY_H

#include <ctime>
#include <string>
#include <vector>
#include <ostream>
#include "Utility.h"

class StockEntry {
public:
    StockEntry(std::string line);

    friend std::ostream &operator<<(std::ostream &os, const StockEntry &entry);

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
