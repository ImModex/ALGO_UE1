#ifndef UE1_STOCKMANAGER_H
#define UE1_STOCKMANAGER_H


#include "HashTable.h"
#include <string>

class StockManager {
public:
    StockManager();
    void add(std::string name, std::string shortname, std::string WKN);
    Stock* get(std::string key);
    void import(std::string filename);
private:
    HashTable nameTable;
    HashTable shortTable;
    Stock importBuffer;
};


#endif //UE1_STOCKMANAGER_H
