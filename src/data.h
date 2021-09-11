//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_DATA_H
#define FJSP_DATA_H

#include "Job.h"
#include "Order.h"
#include "Machine.h"
#include "Occupy.h"
#include <vector>
#include <memory>

namespace data {
    extern std::vector<std::shared_ptr<Job>> job_vec;
    extern std::vector<std::shared_ptr<Order>> order_vec;
    extern std::vector<std::shared_ptr<Machine>> machine_vec;
    extern std::vector<std::shared_ptr<Occupy>> occupy_vec;
}

#endif //FJSP_DATA_H
