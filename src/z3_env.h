//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_Z3_ENV_H
#define FJSP_Z3_ENV_H

#include <z3++.h>

namespace z3_env {
    extern z3::context c;
    extern z3::optimize s;
    extern z3::expr z;
    extern decltype(s.get_model()) m;
    int cast2int(z3::expr &x);
}

#endif //FJSP_Z3_ENV_H
