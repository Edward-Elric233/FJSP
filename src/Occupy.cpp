//
// Created by edward on 2021/9/10.
//

#include "Occupy.h"
#include <cstring>

int Occupy::ID = 0;

char *Occupy::getID() {
    constexpr int SZ = 10;
    static char buf[SZ];
    snprintf(buf, SZ, "O%d", ID++);
    return buf;
}