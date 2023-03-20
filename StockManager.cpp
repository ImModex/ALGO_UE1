#include <iostream>
#include "StockManager.h"

StockManager::StockManager() {
    this->importBuffer = nullptr;
    this->nameTable = new HashTable();
    this->shortTable = new HashTable();
}

StockManager::~StockManager() {
    delete this->importBuffer;
    delete this->nameTable;
    delete this->shortTable;
}

// Infinite loop while program is not exited
void StockManager::start() {
    while (input());
}

// Import stock from user input
void StockManager::import() {
    this->import(Utility::getInput("Please enter the name of the file that you want to import."));
}

// Import stock from given filename
void StockManager::import(std::string filename) {
    std::ifstream file = std::ifstream(filename);
    if (!file.is_open()) {
        std::cout << "File " << filename << " was not found or could not be opened." << std::endl;
        return;
    }

    this->import(file, 1);
    std::cout << "Sucessfully imported file " << filename << std::endl;
}

// Import stock from given filestream, skips certain amount of lines
void StockManager::import(std::ifstream &file, int linesToSkip) {

    for (int i = 0; i < linesToSkip; i++) {
        // Ignore "head" of .csv
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    this->importBuffer = new Stock("", "", "");
    this->importBuffer->fromFile(file, 30);
    file.close();
}

// Puts header info into imported stock and stores it in the tables
void StockManager::add() {
    if (this->importBuffer == nullptr) {
        std::cout << "No stock has been imported yet" << std::endl;
        return;
    }

    std::string name = Utility::getInput("Please enter the name of the stock");
    std::string shortname = Utility::getInput("Please enter the short name of the stock");
    std::string WKN = Utility::getInput("Please enter the ISIN (WKN) of the stock");

    this->add(name, shortname, WKN);
}

void StockManager::add(std::string name, std::string shortname, std::string WKN) {
    if (this->importBuffer == nullptr) {
        std::cout << "No stock has been imported yet" << std::endl;
        return;
    }

    Stock *nameFind = this->get(name), *shortFind = this->get(shortname);
    if (nameFind != nullptr && shortFind != nullptr) {
        std::cout << "Stock with name " << name << " and short name " << shortname << " already exists!" << std::endl;
        return;
    }

    if (nameFind != nullptr) {
        std::cout << "Stock with name " << name << " already exists." << std::endl;
        return;
    }

    if (shortFind != nullptr) {
        std::cout << "Stock with short name " << shortname << " already exists." << std::endl;
        return;
    }

    this->importBuffer->setData(name, shortname, WKN);
    this->nameTable->add(this->importBuffer, name);
    this->shortTable->add(this->importBuffer, shortname);

    this->importBuffer = nullptr;
    std::cout << "Added stock " << name << " successfully." << std::endl;
}

void StockManager::del() {
    this->del(Utility::getInput("Please enter the name or short name of the stock that you want to delete."));
}

// Best Case: O(1)
// Avg. Case: O(1)
// Worst Case: O(n)
// "Deletes" stock with given key from both tables (sets delete flag)
void StockManager::del(std::string key) {
    Stock *elem = this->get(key);
    if (elem == nullptr) {
        std::cout << "Could not delete stock with key " << key << " because it doesn't exist!" << std::endl;
        return;
    }
    elem->del();
    std::cout << "The stock with the key " << key << " was deleted successfully." << std::endl;
}

// Returns stock of given key or nullptr if not found
void StockManager::get() {
    std::string key = Utility::getInput("Please enter the name or short name of the stock you want to find.");
    Stock *stock = this->get(key);

    if (stock == nullptr) {
        std::cout << "Stock with the key " << key << " could not be found." << std::endl;
        return;
    }

    stock->printLastEntry();
}

Stock *StockManager::get(std::string key) {
    Stock *elem = nullptr;

    if (key.length() <= 5)
        elem = this->shortTable->search(key);

    if (elem == nullptr)
        elem = this->nameTable->search(key);

    return (elem == nullptr || !elem->isActive()) ? nullptr : elem;
}

// Saves tables to input filename
void StockManager::save() {
    this->save(Utility::getInput("Please enter the name of the file that you want to save your hashtables to."));
}

void StockManager::save(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not save to file " << filename << "." << std::endl;
        return;
    }

    for (int i = 0; i < Utility::TABLE_LENGTH - 1; i++) {
        if (this->nameTable->isEmpty(i) || !this->nameTable->getStockAt(i)->isActive()) continue;
        file << i << "," << this->nameTable->hash(this->nameTable->getStockAt(i)->getShortname()) << std::endl;
        this->nameTable->getStockAt(i)->printToFile(file);
    }
    std::cout << "File " << filename << " saved successfully!" << std::endl;
    file.close();
}

void StockManager::load() {
    this->load(Utility::getInput("Please enter the name of the file that you want to load."));
}

void StockManager::plot() {
    this->plot(Utility::getInput("Please enter the name of the stock that you want to plot."));
}

// Plots stock with given key
void StockManager::plot(std::string key) {
    if (this->get(key) != nullptr) {
        Stock *stock = this->get(key);
        std::tuple<float, float> stockRange = stock->GetHighLow();

        // Get min and max closing value from current Stock and round it to 2 decimals
        float max = round(std::get<0>(stockRange) * 100.0) / 100.0;
        float min = round(std::get<1>(stockRange) * 100.0) / 100.0;
        // Get step Size
        float stepSize = (max - min) / Utility::PLOT_HEIGHT;
        // Create char array for plot
        char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH * 2];

        for (int i = 0; i < Utility::PLOT_HEIGHT; ++i) {
            for (int j = 0; j < Utility::PLOT_WIDTH * 2; j += 2) {
                // Calculate yValue for current time index
                int yValue = roundf((stock->getClosingAt(j / 2) - min) / stepSize);
                // If current closing value matches the minimum closing value --> yValue would be 0 (x-Axis)
                // --> Change value to 1
                if (!yValue) {
                    yValue = 1;
                }
                // If
                if (i >= Utility::PLOT_HEIGHT - yValue) {
                    // Set x for current index if PLOT_HEIGHT - yValue matches current y-Position
                    graph[i][j] = char(158);
                    graph[i][j + 1] = char(158);
                } else {
                    // Otherwise set space char
                    graph[i][j] = ' ';
                    graph[i][j + 1] = ' ';
                }
            }
        }
        // Get stock data (name, shortname, wkn)
        std::vector<std::string> data = stock->getData();
        printGraph(graph, data, stockRange);

    } else {
        std::cout << "No Stock found for Key '" << key << "'!" << std::endl;
    }
}

// Prints graph of stock to be plotted
void StockManager::printGraph(char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH * 2], std::vector<std::string> data,
                              std::tuple<float, float> stockRange) {
    std::cout << std::endl << "Name: " << data.at(0) << " | Short name: " << data.at(1) << " | ISIN: " << data.at(2)
              << std::endl << std::endl;
    std::cout << "Value(EUR)" << std::endl;
    for (int i = 0; i <= Utility::PLOT_HEIGHT + 1; ++i) {
        if (i == 1) {
            std::cout << std::get<0>(stockRange) << "-";
        } else if (i == Utility::PLOT_HEIGHT) {
            std::cout << std::get<1>(stockRange) << "-";
        } else {
            std::cout << Utility::MARGIN;
        }
        for (int j = 0; j <= (Utility::PLOT_WIDTH + 1) * 2; ++j) {
            if (j == 0 && i == 0) {
                std::cout << Utility::Y_AXIS_ARROW;
            } else if (j == 0 && i <= Utility::PLOT_HEIGHT) {
                std::cout << Utility::Y_AXIS_LINE;
            }
            if (i == Utility::PLOT_HEIGHT + 1) {
                if (j == 0) {
                    std::cout << Utility::BOTTOMLEFTCORNER;
                } else if (j == (Utility::PLOT_WIDTH + 1) * 2) {
                    std::cout << Utility::X_AXIS_ARROW;
                } else {
                    std::cout << Utility::X_AXIS_LINE;
                }
            }
            if (i > 0 && i <= Utility::PLOT_HEIGHT && j > 0 && j <= (Utility::PLOT_WIDTH) * 2) {
                std::cout << graph[i - 1][j - 1];
            }
        }
        if (i != Utility::PLOT_HEIGHT + 1) {
            std::cout << std::endl;
        }
    }
    std::cout << "Time(Days)" << std::endl << Utility::MARGIN;
    for (int i = 0; i <= Utility::PLOT_WIDTH * 2; i++) {
        if (i == 1) {
            std::cout << char(39);
        } else if (i == Utility::PLOT_WIDTH * 2) {
            std::cout << char(39) << std::endl << Utility::MARGIN;
        } else {
            std::cout << " ";
        }
    }
    for (int i = 0; i <= Utility::PLOT_WIDTH * 2; i++) {
        if (i == 1) {
            std::cout << "1";
        } else if (i == Utility::PLOT_WIDTH * 2) {
            std::cout << "30" << std::endl << std::endl;
        } else {
            std::cout << " ";
        }
    }
}

// Loads tables from given filename
void StockManager::load(std::string filename) {

    // Delete old tables and make new ones
    delete this->nameTable;
    delete this->shortTable;

    this->nameTable = new HashTable();
    this->shortTable = new HashTable();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not load file " << filename << "." << std::endl;
        return;
    }

    // Until end of file is reached or error bit is set
    while (!file.eof() && file.good()) {
        // Read indices
        std::string buf;
        std::getline(file, buf);
        if (buf.empty()) break;

        std::vector<std::string> indices = Utility::split(buf, ",");

        // Read stock header
        std::string stockHeader;
        file >> stockHeader;
        file.ignore();

        std::vector<std::string> headerData = Utility::split(stockHeader, ",");

        // Import stock entries
        this->import(file, 0);
        this->add(headerData.at(0), headerData.at(1), headerData.at(2));
    }

    file.close();
    std::cout << "File " << filename << " has been loaded successfully." << std::endl;
}

// Handles input, calls corresponding methods
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
                this->del();
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

// Prints menu
void StockManager::printMenu() {
    std::cout << std::endl
              << "Welcome to the Stock Manager, following commands are available:" << std::endl
              << "(1) - ADD - Adds imported stock to hashtable" << std::endl
              << "(2) - DEL - Deletes stock from hashtable" << std::endl
              << "(3) - IMPORT - Imports stock data from .csv file" << std::endl
              << "(4) - SEARCH - Searches hashtables for stock and prints it, if found" << std::endl
              << "(5) - PLOT - Prints price data of selected stock for past 30 days" << std::endl
              << "(6) - SAVE - Saves hashtables to a file" << std::endl
              << "(7) - LOAD - Loads hashtables from a file" << std::endl
              << "(8) - QUIT - Closes the program" << std::endl;
}