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

std::tuple<float, float> Stock::GetHighLow() {
    // Get max high and min low from hashtable
    float high = this->entries.at(0).getClose();
    float low = this->entries.at(0).getClose();

    for(int i=0; i < 30; ++i) {
        if(this->entries.at(i).getClose() > high) {
            high = this->entries.at(i).getClose();
        }
        if(this->entries.at(i).getClose() < low) {
            low = this->entries.at(i).getClose();
        }
    }

    return std::make_tuple(high, low);
}

float Stock::getClosingAt(int index) {
    return this->entries[index].getClose();
}

const std::vector<std::string> Stock::getData() {
    std::vector<std::string> data;
    data.push_back(this->name);
    data.push_back(this->shortname);
    data.push_back(this->WKN);
    return data;
}
