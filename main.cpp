#include <iostream>
#include "StockManager.h"
#include "Stock.h"

int main() {
    StockManager manager;

    manager.import("MSFT.csv");
    manager.add("Microsoft", "MSFT", "123456");

    std::cout << *manager.get("Microsoft") << std::endl;

    return 0;
}
