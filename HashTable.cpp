#include <iostream>
#include "HashTable.h"

// Initialize table with table length
HashTable::HashTable() {
    this->table = new Stock[Utility::TABLE_LENGTH];
}

// Best Case: O(1)
// Avg. Case: O(1)
// Worst Case: O(n)
// Adds a stock to the table, uses quadratic probing if index is taken
void HashTable::add(Stock &stock, std::string key) {
    int index = this->hash(key);
    int jumpCount = 1;
    int newIndex = index;

    while (!this->table[newIndex].getName().empty() && this->table[newIndex].isActive()) {
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

    if (this->table[newIndex].getName().empty()) return nullptr;

    while (this->table[newIndex].getName() != key && this->table[newIndex].getShortname() != key) {
        newIndex = Utility::quadraticProbing(jumpCount++, index);
        if (newIndex == -1) return nullptr;
    }

    Stock *element = &this->table[newIndex];
    return (element->getName() == key || element->getShortname() == key) ? element : nullptr;
}

// Hashes a stock name or short name to generate key (index) for the table
int HashTable::hash(std::string key) {
    unsigned long hash = 67;
    int i=1;

    std::for_each(key.begin(), key.end(), [&](const auto &item) {
        hash = (item*hash*++i) + item;
    });

    return (hash % (Utility::TABLE_LENGTH - 1));
}

// Returns whether index is empty or not
bool HashTable::isEmpty(int index) {
    return this->table[index].getName().empty();
}

// Returns stock at index
Stock *HashTable::getStockAt(int index) {
    return &this->table[index];
}

// Free allocated memory
HashTable::~HashTable() {
    delete[] this->table;
}

