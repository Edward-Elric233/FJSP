#include "work.h"
#include <iostream>
#include <fstream>

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream is("../data/data0.txt");
    read(is);
    //TODO: DEBUG STATEMENTS
    test_read();
    add_constraints();
    solve(std::cout);
    return 0;
}
