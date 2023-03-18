#ifndef UE1_STOCKMANAGER_H
#define UE1_STOCKMANAGER_H


#include "HashTable.h"
#include <string>
#include <limits>

class StockManager {
public:
    StockManager();
    void add(std::string name, std::string shortname, std::string WKN);
    Stock* get(std::string key);
    void import(std::string filename);
    void save();
    void load();
private:
    HashTable nameTable;
    HashTable shortTable;
    Stock importBuffer;
};


#endif //UE1_STOCKMANAGER_H
