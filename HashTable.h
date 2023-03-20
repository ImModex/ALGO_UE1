#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Stock.h"
#include <limits>
#include <cmath>

// Class that represents the hash table itself
class HashTable {
public:
    HashTable();
    virtual ~HashTable();

    // Add and search elements in the table
    void add(Stock &stock, std::string key);
    Stock *search(std::string key);

    // Hash function to get the index for a value
    int hash(std::string key);

    bool isEmpty(int index);
    Stock* getStockAt(int index);
private:
    Stock *table;
};


#endif
