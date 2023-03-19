#include <iostream>
#include "Stock.h"

Stock::Stock() : Stock("", "", "") {}

Stock::Stock(std::string name, std::string shortname, std::string WKN) {
    this->name = std::move(name);
    this->shortname = std::move(shortname);
    this->WKN = std::move(WKN);
}

void Stock::fromFile(std::ifstream &fs) {
    fromFile(fs, 100000);
}

void Stock::fromFile(std::ifstream &fs, int maxLines) {
    if(!fs.is_open()) return;

    int lineCount = 0;
    std::vector<std::string> lines;
    std::string buf;
    while(lineCount++ < maxLines && std::getline(fs, buf)) {
        lines.push_back(buf);
    }
    std::reverse(lines.begin(), lines.end());

    for(int i = 0; i < 30; i++) {
        this->entries.emplace_back(StockEntry(lines.at(i)));
    }
    std::reverse(this->entries.begin(), this->entries.end());
}

std::ostream &operator<<(std::ostream &os, const Stock &stock) {
    os << "name: " << stock.name << " shortname: " << stock.shortname << " WKN: " << stock.WKN << " entries: " << std::endl;
    for(int i = 0; i < 30; i++) {
        os << stock.entries.at(i) << std::endl;
    }
    return os;
}

void Stock::setData(std::string name, std::string shortname, std::string WKN) {
    this->name = name;
    this->shortname = shortname;
    this->WKN = WKN;
}

const std::string &Stock::getName() const {
    return name;
}

const std::string &Stock::getShortname() const {
    return shortname;
}

void Stock::printToFile(std::ofstream &file) {
    file << this->name << "," << this->shortname << "," << this->WKN << std::endl;
    for(int i = 0; i < 30; i++) {
        this->entries.at(i).printToFile(file);
    }
}
