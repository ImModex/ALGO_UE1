#include <iostream>
#include "HashTable.h"

// Initialize table with table length
HashTable::HashTable() {
    this->table = new Stock *[Utility::TABLE_LENGTH];
    for (int i = 0; i < Utility::TABLE_LENGTH; i++) {
        this->table[i] = nullptr;
    }
}

// Best Case: O(1)
// Avg. Case: O(1)
// Worst Case: O(n)
// Adds a stock to the table, uses quadratic probing if index is taken
void HashTable::add(Stock *stock, std::string key) {
    int index = this->hash(key);
    int jumpCount = 1;
    int newIndex = index;

    while (!this->isEmpty(newIndex) && this->table[newIndex]->isActive()) {
        newIndex = Utility::quadraticProbing(jumpCount++, index);
        if (newIndex == -1) return;
    }
    this->table[newIndex] = stock;
}

// Best Case: O(1)
// Avg. Case: O(1)
// Worst Case: O(n)
// Searches for key in the table, keeps quadratic probing in mind
Stock *HashTable::search(std::string key) {
    int index = this->hash(key);
    int jumpCount = 1;
    int newIndex = index;

    if (this->isEmpty(newIndex)) return nullptr;

    while (this->table[newIndex]->getName() != key && this->table[newIndex]->getShortname() != key) {
        newIndex = Utility::quadraticProbing(jumpCount++, index);
        if (newIndex == -1) return nullptr;
    }

    Stock *element = this->table[newIndex];
    return (element->getName() == key || element->getShortname() == key) ? element : nullptr;
}

// Hashes a stock name or short name to generate key (index) for the table
int HashTable::hash(std::string key) {
    unsigned long hash = 5381;

    std::for_each(key.begin(), key.end(), [&](const auto &item) {
        hash = ((hash << 5) + hash) + item;
    });

    return (hash % (Utility::TABLE_LENGTH - 1));
}

// Returns whether index is empty or not
bool HashTable::isEmpty(int index) {
    return this->table[index] == nullptr || this->table[index]->getName().empty();
}

// Returns stock at index
Stock *HashTable::getStockAt(int index) {
    return this->table[index];
}


bool HashTable::deleted = false;
// Free allocated memory
HashTable::~HashTable() {
    // If already deleted, only delete array
    if(!HashTable::deleted) {
        for (int i = 0; i < Utility::TABLE_LENGTH; i++) {
            delete this->table[i];
        }
    }
    //HashTable::setDeleted();
    delete[] this->table;
    HashTable::deleted = true;
}

