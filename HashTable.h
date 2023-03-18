#ifndef UE1_HASHTABLE_H
#define UE1_HASHTABLE_H

#define TABLE_LENGTH 23

#include "Stock.h"
#include <limits>

class HashTable {
public:
    HashTable();
    virtual ~HashTable();
    void add(Stock &stock, std::string key);
    Stock *search(std::string key);
    void save(std::string filename);
    void load(std::string filename);
    int hash(std::string key);

    bool isEmpty(int index);
    Stock* getStockAt(int index);
private:
    Stock *table;
};


#endif //UE1_HASHTABLE_H
