#include <iostream>
#include "StockManager.h"
#include "Stock.h"

#include <fstream>
int main() {

    std::ifstream str;
    str.open("F:\\keep\\Zeug\\Schule\\FH\\2. Semester\\ALGO\\UE1\\MSFT.csv", std::ifstream::in);
    Stock msft("Microsoft", "MSFT", "123456");
    msft.fromFile(str);

    std::cout << msft << std::endl;

    return 0;
}
