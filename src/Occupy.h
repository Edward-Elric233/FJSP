//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_OCCUPY_H
#define FJSP_OCCUPY_H

#include "z3_env.h"

class Occupy {
    static int ID;
    static char *getID();
public:
    z3::expr occupy;
    int job_idx;
    int order_idx;
    int machine_idx;
    int time;
    Occupy(int _job_idx, int _order_idx, int _machine_idx, int _time)
    : job_idx(_job_idx)
    , order_idx(_order_idx)
    , machine_idx(_machine_idx)
    , time(_time)
    , occupy(z3_env::c.int_const(getID())) {
        z3_env::s.add(occupy == 0 || occupy == 1);
    }
};


#endif //FJSP_OCCUPY_H
