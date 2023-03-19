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

                //std::cout << "yValue: " << yValue << std::endl;
                if(i >= Utility::PLOT_HEIGHT-yValue) {
                    graph[i][j] = char(158);
                    graph[i][j+1] = char(158);
                } else {
                    graph[i][j] = ' ';
                    graph[i][j+1] = ' ';
                }

                /*if(i == Utility::PLOT_HEIGHT-yValue) {
                    graph[i][j] = 'x';
                } else {
                    graph[i][j] = ' ';
                }*/
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
