#include <iostream>
#include "HashTable.h"

HashTable::HashTable() {
    this->table = new Stock[TABLE_LENGTH];
}

void HashTable::add(Stock &stock, std::string key) {
    int index = this->hash(key);
    this->table[index] = stock;
    // TODO: Collision handling
}

Stock *HashTable::search(std::string key) {
    Stock* element = &this->table[this->hash(key)];
    return (element->getName() == key || element->getShortname() == key) ? element : nullptr;
}

void HashTable::save() {

}

void HashTable::load() {

}

int HashTable::hash(std::string key) {
    unsigned long hash = 5381;

    std::for_each(key.begin(), key.end(), [&](const auto &item) {
       hash = ((hash << 5) + hash) + item;
    });

    return (hash % (TABLE_LENGTH-1));
}

HashTable::~HashTable() {
    delete[] this->table;
}
