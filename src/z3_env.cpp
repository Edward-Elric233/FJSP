// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2021/9/10
// Description: 
#include "z3_env.h"
#include <sstream>

namespace z3_env {
    z3::context c;
    z3::optimize s(c);
    z3::expr z = c.int_const("z");
    decltype(s.get_model()) m  = s.get_model();
    int cast2int(z3::expr &x) {
        std::ostringstream os;
        os << m.eval(x);
        return std::stoi(os.str());
    }
}