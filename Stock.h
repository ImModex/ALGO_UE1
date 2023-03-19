#ifndef UE1_STOCK_H
#define UE1_STOCK_H

#include <string>
#include <vector>
#include "StockEntry.h"
#include <fstream>
#include <algorithm>
#include <utility>
#include <ostream>
#include <tuple>

class Stock {
public:
    Stock();
    Stock(std::string name, std::string shortname, std::string WKN);

    const std::string &getName() const;
    const std::string &getShortname() const;
    const std::vector<std::string> getData();

    void setData(std::string name, std::string shortname, std::string WKN);
    void fromFile(std::ifstream &fs);
    void fromFile(std::ifstream &fs, int maxLines);

    void printToFile(std::ofstream &file);
    friend std::ostream &operator<<(std::ostream &os, const Stock &stock);

    std::tuple<float, float> GetHighLow();
    float getClosingAt(int index);

private:
    std::string name;
    std::string shortname;
    std::string WKN;
    std::vector<StockEntry> entries;
};


#endif
