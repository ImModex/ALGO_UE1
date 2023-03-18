#include <iostream>
#include "StockManager.h"

StockManager::StockManager() {

}

void StockManager::import(std::string filename) {
    std::ifstream ifstream = std::ifstream(filename, std::ifstream::in);

    if (!ifstream.is_open()) {
        std::cout << "File " << filename << " was not found or could not be opened." << std::endl;
        return;
    }

    // Ignore "head" of .csv
    ifstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->importBuffer = Stock("", "", "");
    this->importBuffer.fromFile(ifstream);

    std::cout << "Sucessfully imported file " << filename << std::endl;
}

void StockManager::add(std::string name, std::string shortname, std::string WKN) {
    this->importBuffer.setData(name, shortname, WKN);
    this->nameTable.add(this->importBuffer, name);
    this->shortTable.add(this->importBuffer, shortname);
}

Stock* StockManager::get(std::string key) {
    Stock* elem = nullptr;

    if(key.length() <= 5)
        elem = this->shortTable.search(key);

    if(elem == nullptr)
        elem = this->nameTable.search(key);

    return elem;
}

void StockManager::save() {
    this->nameTable.save("nametable.dat");
    this->shortTable.save("shorttable.dat");
}

void StockManager::load() {
    this->nameTable.load("nametable.dat");
    this->shortTable.load("shorttable.dat");
}
