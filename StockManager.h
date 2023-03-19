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
    virtual ~StockManager();

    void add();
    void add(std::string name, std::string shortname, std::string WKN);

    Stock* get();
    Stock* get(std::string key);

    void import();
    void import(std::string filename);

    void save();
    void save(std::string filename);

    void load();
    void plot(std::string key);
    
    void load(std::string filename);
    bool input();
private:
    void printMenu();
    void import(std::ifstream &file, int linesToSkip);

    HashTable nameTable;
    HashTable shortTable;
    Stock *importBuffer;
    
    void printGraph(char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH*2]);
};


#endif //UE1_STOCKMANAGER_H
