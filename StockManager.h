#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H


#include "HashTable.h"
#include <string>
#include <limits>
 #include <cmath>

// Class that represents the program, it manages the tables and buffers
class StockManager {
public:
    StockManager();
    virtual ~StockManager();

    // Adds imported stock to the tables
    void add();
    void add(std::string name, std::string shortname, std::string WKN);

    // "Deletes" stock from tables (sets delete flag)
    void del();
    void del(std::string key);

    // Gets stock from the tables (returns nullptr if not found)
    void get();
    Stock* get(std::string key);

    // Imports stock from file and stores it in import buffer waiting to be added with add()
    void import();
    void import(std::string filename);

    // Saves tables to file
    void save();
    void save(std::string filename);

    // Loads tables from file
    void load();
    void load(std::string filename);

    // Plots stock of given key
    void plot();
    void plot(std::string key);

    // Handles console input
    bool input();

    // Starts the manager program
    void start();
private:
    void printMenu();
    void import(std::ifstream &file, int linesToSkip);

    // Seperate tables for name and short name
    HashTable nameTable;
    HashTable shortTable;
    Stock *importBuffer;
    
    void printGraph(char graph[Utility::PLOT_HEIGHT][Utility::PLOT_WIDTH*2], std::vector<std::string> data, std::tuple<float, float> stockRange);
};


#endif
