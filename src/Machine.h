//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_MACHINE_H
#define FJSP_MACHINE_H

#include <vector>

class Machine {
public:
    int idx;
    std::vector<int> occupy_vec;
    Machine(int _idx) : idx(_idx) {}
};


#endif //FJSP_MACHINE_H
