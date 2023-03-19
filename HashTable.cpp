#include <iostream>
#include "HashTable.h"

HashTable::HashTable() {
    this->table = new Stock[Utility::TABLE_LENGTH];
}

void HashTable::add(Stock &stock, std::string key) {
    int index = this->hash(key);
    int jumpCount = 1;
    int newIndex = index;

    while(!this->table[newIndex].getName().empty() || !this->table[newIndex].isActive()) {
        newIndex = Utility::quadraticProbing(jumpCount++, index);
        if(newIndex == -1) return;
    }
    this->table[newIndex] = stock;
}

Stock *HashTable::search(std::string key) {
    int index = this->hash(key);
    int jumpCount = 1;
    int newIndex = index;

    if(this->table[newIndex].getName().empty()) return nullptr;

    while(this->table[newIndex].getName() != key && this->table[newIndex].getShortname() != key) {
        newIndex = Utility::quadraticProbing(jumpCount++, index);
        if(newIndex == -1) return nullptr;
    }

    Stock* element = &this->table[newIndex];
    return (element->getName() == key || element->getShortname() == key) ? element : nullptr;
}

int HashTable::hash(std::string key) {
    unsigned long hash = 5381;

    std::for_each(key.begin(), key.end(), [&](const auto &item) {
       hash = ((hash << 5) + hash) + item;
    });

    return (hash % (Utility::TABLE_LENGTH-1));
}

HashTable::~HashTable() {
    delete[] this->table;
}

bool HashTable::isEmpty(int index) {
    return this->table[index].getName().empty();
}

Stock *HashTable::getStockAt(int index) {
    return &this->table[index];
}
