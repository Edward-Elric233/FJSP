//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_ORDER_H
#define FJSP_ORDER_H

#include "z3_env.h"
#include <vector>

class Order {
    static int BID;
    static int EID;
    static char *getBID();
    static char *getEID();
public:
    int job_idx;
    int idx;
    z3::expr B;
    z3::expr E;
    std::vector<int> occupy_vec;
    Order(int _job_idx, int _idx)
    : job_idx(_job_idx)
    , idx(_idx)
    , B(z3_env::c.int_const(getBID()))
    , E(z3_env::c.int_const(getEID())) {
        z3_env::s.add(B >= 0);
    }
};


#endif //FJSP_ORDER_H
