#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include "StockEntry.h"
#include <fstream>
#include <algorithm>
#include <utility>
#include <ostream>
#include <tuple>

// Class that represents a stock with header data like name, short name and WKN and 30 entries
class Stock {
public:
    Stock();
    Stock(std::string name, std::string shortname, std::string WKN);
    virtual ~Stock() = default;

    // Get stock information
    const std::string &getName() const;
    const std::string &getShortname() const;

    // Data contains the entire stock header
    std::vector<std::string> getData();
    void setData(std::string name, std::string shortname, std::string WKN);

    // Imports entries from a file
    void fromFile(std::ifstream &fs, int maxLines);

    // Prints stock to a file or ostream
    void printToFile(std::ofstream &file);
    friend std::ostream &operator<<(std::ostream &os, const Stock &stock);
    void printLastEntry();

    // Get highest and lowest closing value
    std::tuple<float, float> GetHighLow();
    float getClosingAt(int index);

    // Set / Get delete flag of stock
    void del();
    bool isActive() const;
private:
    bool deleted;
    bool active;
    std::string name;
    std::string shortname;
    std::string WKN;
    std::vector<StockEntry> entries;
};


#endif
