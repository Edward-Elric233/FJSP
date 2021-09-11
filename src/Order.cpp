//
// Created by edward on 2021/9/10.
//

#include "Order.h"

int Order::BID = 0;
int Order::EID = 0;

char *Order::getBID() {
    constexpr int SZ = 10;
    static char buf[SZ];
    snprintf(buf, SZ, "B%d", BID++);
    return buf;
}

char *Order::getEID() {
    constexpr int SZ = 10;
    static char buf[SZ];
    snprintf(buf, SZ, "E%d", EID++);
    return buf;
}