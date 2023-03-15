#ifndef UE1_STOCKMANAGER_H
#define UE1_STOCKMANAGER_H


#include "HashTable.h"
#include <string>

class StockManager {
public:
    StockManager();
    void fromFile(std::string &filename);
private:
    HashTable nameTable;
    HashTable shortTable;
};


#endif //UE1_STOCKMANAGER_H
