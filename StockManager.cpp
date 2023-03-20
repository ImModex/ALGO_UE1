#include <iostream>
#include "StockManager.h"

StockManager::StockManager() {
    this->importBuffer = nullptr;
    while(input());
}

StockManager::~StockManager() {
    delete this->importBuffer;
}

void StockManager::import() {
    this->import(Utility::getInput("Please enter the name of the file that you want to import."));
}

void StockManager::import(std::string filename) {
    std::ifstream file = std::ifstream(filename);
    if (!file.is_open()) {
        std::cout << "File " << filename << " was not found or could not be opened." << std::endl;
        return;
    }

    this->import(file, 1);
    std::cout << "Sucessfully imported file " << filename << std::endl;
}

void StockManager::import(std::ifstream &file, int linesToSkip) {

    for(int i = 0; i < linesToSkip; i++) {
        // Ignore "head" of .csv
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    this->importBuffer = new Stock("", "", "");
    this->importBuffer->fromFile(file);
}

void StockManager::add() {
    if(this->importBuffer == nullptr) {
        std::cout << "No stock has been imported yet" << std::endl;
        return;
    }

    std::string name = Utility::getInput("Please enter the name of the stock");
    std::string shortname = Utility::getInput("Please enter the short name of the stock");
    std::string WKN = Utility::getInput("Please enter the ISIN (WKN) of the stock");

    this->add(name, shortname, WKN);
}

void StockManager::add(std::string name, std::string shortname, std::string WKN) {
    if(this->importBuffer == nullptr) {
        std::cout << "No stock has been imported yet" << std::endl;
        return;
    }

    this->importBuffer->setData(name, shortname, WKN);
    this->nameTable.add(*this->importBuffer, name);
    this->shortTable.add(*this->importBuffer, shortname);

    delete this->importBuffer;
    this->importBuffer = nullptr;
}

Stock* StockManager::get() {
    return this->get(Utility::getInput("Please enter the name or short name of the stock you want to find."));
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
    this->save(Utility::getInput("Please enter the name of the file that you want to save your hashtables to."));
}

void StockManager::save(std::string filename) {
    std::ofstream file(filename);
    if(!file.is_open()) return;

    for(int i = 0; i < TABLE_LENGTH-1; i++) {
        if(this->nameTable.isEmpty(i)) continue;
        file << i << "," << this->nameTable.hash(this->nameTable.getStockAt(i)->getShortname()) << std::endl;
        this->nameTable.getStockAt(i)->printToFile(file);
    }
    file.close();
}

void StockManager::load() {
    this->load(Utility::getInput("Please enter the name of the file that you want to load."));
}

void StockManager::plot() {
    this->plot(Utility::getInput("Please enter the name of the stock that you want to plot."));
}

void StockManager::plot(std::string key) {
    if(this->get(key) != nullptr) {
        std::tuple<float, float> stockRange = this->get(key)->GetHighLow();
        float max = std::get<0>(stockRange);
        float min = std::get<1>(stockRange);
        float stepSize = (max - min) / Utility::PLOT_HEIGHT;
        char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH*2];

        for(int i=0; i < Utility::PLOT_HEIGHT; ++i) {
            for(int j=0; j < Utility::PLOT_WIDTH*2; j+=2) {
                int yValue = roundf((this->get(key)->getClosingAt(j/2) - min) / stepSize);
                if(!yValue) {
                    yValue = 1;
                }

                if(i >= Utility::PLOT_HEIGHT-yValue) {
                    graph[i][j] = char(158);
                    graph[i][j+1] = char(158);
                } else {
                    graph[i][j] = ' ';
                    graph[i][j+1] = ' ';
                }
            }
        }

        printGraph(graph);

    } else {
        std::cout << "No Stock found for Key '" << key << "'!" << std::endl;
    }
}

void StockManager::printGraph(char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH*2]) {
    std::cout << std::endl << std::endl;

    for(int i=0; i <= Utility::PLOT_HEIGHT+1; ++i) {
        for(int j=0; j <= (Utility::PLOT_WIDTH+1)*2; ++j) {
            if(j == 0 && i == 0) {
                std::cout << Utility::Y_AXIS_ARROW;
            } else if(j == 0 && i <= Utility::PLOT_HEIGHT) {
                std::cout << Utility::Y_AXIS_LINE;
            }
            if(i == Utility::PLOT_HEIGHT+1) {
                if(j == 0) {
                    std::cout << Utility::BOTTOMLEFTCORNER;
                } else if(j == (Utility::PLOT_WIDTH+1)*2) {
                    std::cout << Utility::X_AXIS_ARROW;
                } else {
                    std::cout << Utility::X_AXIS_LINE;
                }
            }
            if(i > 0 && i <= Utility::PLOT_HEIGHT && j > 0 && j <= (Utility::PLOT_WIDTH)*2) {
                std::cout << graph[i-1][j-1];
            }
        }
        std::cout << std::endl;
    }
}

void StockManager::load(std::string filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << "File " << "'" << filename << "'" << " could not be opened/found!" << std::endl;
        return;
    }

    while(!file.eof() && file.good()) {
        std::string buf;
        std::getline(file, buf);
        if(buf.empty()) return;

        std::vector<std::string> indices = Utility::split(buf, ",");

        std::string stockHeader;
        file >> stockHeader;
        file.ignore();

        std::vector<std::string> headerData = Utility::split(stockHeader, ",");

        this->import(file, 0);
        this->add(headerData.at(0), headerData.at(1), headerData.at(2));
    }
}

bool StockManager::input() {
    printMenu();
    int input;

    do {
        std::cin >> input;
        switch (input) {
            case 1:
                this->add();
                break;
            case 2:
              //  this->del();
                break;
            case 3:
                this->import();
                break;
            case 4:
                this->get();
                break;
            case 5:
                this->plot();
                break;
            case 6:
                this->save();
                break;
            case 7:
                this->load();
                break;
            case 8:
                return false;
        }
    } while (input < 1 || input > 8);
    return true;
}

void StockManager::printMenu() {
    std::cout << std::endl << "Welcome to the Stock Manager, following commands are available:" << std::endl
                           << "(1) - ADD - Adds imported stock to hashtable" << std::endl
                           << "(2) - DEL - Deletes stock from hashtable" << std::endl
                           << "(3) - IMPORT - Imports stock data from .csv file" << std::endl
                           << "(4) - SEARCH - Searches hashtables for stock and prints it, if found" << std::endl
                           << "(5) - PLOT - Prints price data of selected stock for past 30 days" << std::endl
                           << "(6) - SAVE - Saves hashtables to a file" << std::endl
                           << "(7) - LOAD - Loads hashtables from a file" << std::endl
                           << "(8) - QUIT - Closes the program" << std::endl;
}