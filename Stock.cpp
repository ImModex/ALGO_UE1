#include <iostream>
#include "Stock.h"

// Init empty stocks with empty data
Stock::Stock() : Stock("", "", "") {}

Stock::Stock(std::string name, std::string shortname, std::string WKN) {
    this->name = std::move(name);
    this->shortname = std::move(shortname);
    this->WKN = std::move(WKN);
    this->active = true;
    this->deleted = false;
}

// Imports entries from a given file
void Stock::fromFile(std::ifstream &fs, int maxLines) {
    // File does not exist / cannot be opened
    if (!fs.is_open()) return;

    // Import lines from file
    int lineCount = 0;
    std::vector<std::string> lines;
    std::string buf;
    while (lineCount++ < maxLines && std::getline(fs, buf)) {
        lines.push_back(buf);
    }
    // Reverse
    std::reverse(lines.begin(), lines.end());

    // Take first 30 lines of reversed -> last 30 entries
    for (int i = 0; i < 30; i++) {
        this->entries.emplace_back(StockEntry(lines.at(i)));
    }
    std::reverse(this->entries.begin(), this->entries.end());
}

// Print stock header + entries to ostream
std::ostream &operator<<(std::ostream &os, const Stock &stock) {
    os << "name: " << stock.name << " shortname: " << stock.shortname << " WKN: " << stock.WKN << " entries: "
       << std::endl;
    for (int i = 0; i < 30; i++) {
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

// Print stock header + entries to file
void Stock::printToFile(std::ofstream &file) {
    file << this->name << "," << this->shortname << "," << this->WKN << std::endl;
    for (int i = 0; i < 30; i++) {
        this->entries.at(i).printToFile(file);
    }
}

std::tuple<float, float> Stock::GetHighLow() {
    // Get max high and min low from hashtable
    float high = this->entries.at(0).getClose();
    float low = this->entries.at(0).getClose();

    for (int i = 0; i < 30; ++i) {
        if (this->entries.at(i).getClose() > high) {
            high = this->entries.at(i).getClose();
        }
        if (this->entries.at(i).getClose() < low) {
            low = this->entries.at(i).getClose();
        }
    }
    // Round values to 2 decimals
    high = round(high * 100.0) / 100.0;
    low = round(low * 100.0) / 100.0;

    return std::make_tuple(high, low);
}

float Stock::getClosingAt(int index) {
    return this->entries[index].getClose();
}

// Returns array containing stock header
std::vector<std::string> Stock::getData() {
    std::vector<std::string> data;
    data.push_back(this->name);
    data.push_back(this->shortname);
    data.push_back(this->WKN);
    return data;
}

void Stock::del() {
    this->active = false;
}

bool Stock::isActive() const {
    return this->active;
}

void Stock::printLastEntry() {
    std::cout << this->entries.at(this->entries.size() - 1) << std::endl;
}
