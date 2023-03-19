#ifndef UE1_STOCKMANAGER_H
#define UE1_STOCKMANAGER_H


#include "HashTable.h"
#include <string>
#include <limits>
#include "console.h"
#include <cmath>

class StockManager {
public:
    StockManager();
    void add(std::string name, std::string shortname, std::string WKN);
    Stock* get(std::string key);
    void import(std::string filename);
    void save();
    void load();
    void plot(std::string key);
private:
    HashTable nameTable;
    HashTable shortTable;
    Stock importBuffer;

    void printGraph(char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH*2]);
};


#endif //UE1_STOCKMANAGER_H
