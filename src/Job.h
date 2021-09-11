//
// Created by edward on 2021/9/10.
//

#ifndef FJSP_JOB_H
#define FJSP_JOB_H

#include <vector>

class Job {
public:
    int idx;
    std::vector<int> order_vec;
    Job(int _idx) : idx(_idx) {}
};


#endif //FJSP_JOB_H
