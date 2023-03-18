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

void HashTable::save(std::string filename) {
    std::ofstream file(filename);
    if(!file.is_open()) return;

    for(int i = 0; i < TABLE_LENGTH-1; i++) {
        if(this->table[i].getName().empty()) continue;
        file << i << std::endl;
        this->table[i].printToFile(file);
    }
    file.close();
}

void HashTable::load(std::string filename) {
    std::ifstream file(filename);
    if(!file.is_open()) return;

    while(!file.eof()) {
        int index;
        file >> index;

        std::string stockHeader;
        file >> stockHeader;
        file.ignore();

        std::vector<std::string> headerData = Utility::split(stockHeader, ",");

        this->table[index] = Stock(headerData.at(0), headerData.at(1), headerData.at(2));
        this->table[index].fromFile(file);
    }
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
