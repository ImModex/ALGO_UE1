#ifndef UE1_HASHTABLE_H
#define UE1_HASHTABLE_H

#include "Stock.h"
#include <limits>
#include <cmath>

class HashTable {
public:
    HashTable();
    virtual ~HashTable();
    void add(Stock &stock, std::string key);
    Stock *search(std::string key);
    int hash(std::string key);

    bool isEmpty(int index);
    Stock* getStockAt(int index);
private:
    Stock *table;
};


#endif //UE1_HASHTABLE_H
