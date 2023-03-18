#include <iostream>
#include "StockManager.h"
#include "Stock.h"

int main() {
    StockManager manager;

    /*
    manager.import("MSFT.csv");
    manager.add("Microsoft", "MSFT", "123456");

    manager.import("BTC.csv");
    manager.add("Bitcoin", "BTC", "654321");
     */

    manager.load();
    std::cout << *manager.get("Microsoft") << std::endl;
    std::cout << *manager.get("BTC") << std::endl;

   //manager.save();
    return 0;
}
