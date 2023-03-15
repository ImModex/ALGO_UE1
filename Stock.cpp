#include <iostream>
#include "Stock.h"

Stock::Stock(std::string name, std::string shortname, std::string WKN) {
    this->name = std::move(name);
    this->shortname = std::move(shortname);
    this->WKN = std::move(WKN);
}

void Stock::fromFile(std::ifstream &fs) {
    if(!fs.is_open()) return;

    std::vector<std::string> lines;
    std::string buf;
    while(std::getline(fs, buf)) {
        lines.push_back(buf);
    }
    std::reverse(lines.begin(), lines.end());
    for(int i = 0; i < 30; i++) {
        this->entries.emplace_back(lines.at(i));
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
