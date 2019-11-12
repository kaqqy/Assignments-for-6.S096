#include "mst.h"
#include <iostream>
#include <iomanip>

int main() {
    AdjacencyList al(std::cin);
    std::cout << std::fixed << std::setprecision(8) << al.mst() << std::endl;
    return 0;
}
