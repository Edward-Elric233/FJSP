// Copyright(C), Edward-Elric233
// Author: Edward-Elric233
// Version: 1.0
// Date: 2021/9/10
// Description: 
#include "work.h"
#include "data.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace data;

void read(std::istream &is) {
    int N, M, C, K, S, G, D;
    is >> N >> M >> C;
    for (int i = 0; i < M; ++i) {
        machine_vec.emplace_back(new Machine(i));
    }
    for (int i = 0; i < N; ++i) {
        int job_idx = i;
        job_vec.emplace_back(new Job(job_idx));
        is >> K;
        auto &job = job_vec.back();
        //K个工序
        for (int j = 0; j < K; ++j) {
            int order_idx = order_vec.size();
            job->order_vec.push_back(order_idx);
            order_vec.emplace_back(new Order(job_idx, j));
            auto &order = order_vec.back();
            is >> S;
            //S个机器
            for (int k = 0; k < S; ++k) {
                is >> G >> D;
                int occupy_idx = occupy_vec.size();
                occupy_vec.emplace_back(new Occupy(job_idx, order_idx, G, D));
                machine_vec[G]->occupy_vec.push_back(occupy_idx);
                order->occupy_vec.push_back(occupy_idx);
            }
        }
    }
}

void add_constraints() {
    for (auto &job : job_vec) {
        int last_order_idx = job->order_vec.back();
        //约束：z >= E
        z3_env::s.add(z3_env::z >= order_vec[last_order_idx]->E);
        for (int i = 1; i < job->order_vec.size(); ++i) {
            int pre_order_idx = job->order_vec[i - 1];
            int order_idx = job->order_vec[i];
            //约束：B_i >= E_i-1
            z3_env::s.add(order_vec[order_idx]->B >= order_vec[pre_order_idx]->E);
        }
    }

    for (auto &order : order_vec) {
        z3::expr t = z3_env::c.int_val(0);
        for (auto occupy_idx : order->occupy_vec) {
            t = t + occupy_vec[occupy_idx]->occupy;
        }
        //约束：只能运行1台机器
        z3_env::s.add(t == 1);
    }

    for (auto &occupy : occupy_vec) {
        auto &order = order_vec[occupy->order_idx];
        //约束：如果在某台机器上运行，则E == B + time
        z3_env::s.add(z3::implies(occupy->occupy == 1, order->E == order->B + occupy->time));
    }

    for (auto &machine : machine_vec) {
        for (int i = 0; i < machine->occupy_vec.size(); ++i) {
            for (int j = i + 1; j < machine->occupy_vec.size(); ++j) {
                auto &occupy1 = occupy_vec[machine->occupy_vec[i]];
                auto &occupy2 = occupy_vec[machine->occupy_vec[j]];
                auto &order1 = order_vec[occupy1->order_idx];
                auto &order2 = order_vec[occupy2->order_idx];
                //约束：同一台机器不能被多次占用
                z3_env::s.add(z3::implies(occupy1->occupy + occupy2->occupy == 2,
                                          order1->B >= order2->E || order2->B >= order1->E));
            }
        }
    }

//    cout << z3_env::s << endl;
}

class OrderTmp {
public:
    int order_idx;
    int end_time;
    OrderTmp(int _order_idx)
    : order_idx(_order_idx)
    , end_time(z3_env::cast2int(order_vec[_order_idx]->E)) {}
};

bool operator < (const OrderTmp &lhs, const OrderTmp &rhs) {
    return lhs.end_time < rhs.end_time;
}

#include <set>
void output(std::ostream &os) {
    //TODO: DEBUG STATEMENTS
    cout << z3_env::m.eval(z3_env::z) << "\n";
    for (auto &machine : machine_vec) {
        std::set<OrderTmp> order_set;
        for (auto occupy_idx : machine->occupy_vec) {
            auto &occupy = occupy_vec[occupy_idx];
            if (z3_env::cast2int(occupy->occupy) == 1) {
                order_set.insert(OrderTmp(occupy->order_idx));
            }
        }
        os << order_set.size();
        for (auto &order_tmp : order_set) {
            auto &order = order_vec[order_tmp.order_idx];
            os << " " << order->job_idx << " " << order->idx;
            //TODO: DEBUG STATEMENTS
            os << " [ " << z3_env::cast2int(order->B) << ", " << z3_env::cast2int(order->E) << " ] ";
        }
        os << "\n";
    }
}

void solve(std::ostream &os) {
    z3_env::s.minimize(z3_env::z);
    clock_t start = clock();
    auto result = z3_env::s.check();
    clock_t end = clock();
    //TODO: DEBUG STATEMENTS
    cout << "time used: " << (static_cast<double>(end) - start) / CLOCKS_PER_SEC << " s\n";
    if (result == z3::unsat) {
        //TODO: DEBUG STATEMENTS
        cout << "no solution\n";
    } else {
        //TODO: DEBUG STATEMENTS
        cout << "soluted\n";
        z3_env::m = z3_env::s.get_model();
        output(os);
    }
}

#include <ostream>
void test_read() {
    cout << job_vec.size() << " " << machine_vec.size() << " 2\n";
    for (auto &job : job_vec) {
        cout << job->order_vec.size();
        for (auto order_idx : job->order_vec) {
            auto &order = order_vec[order_idx];
            cout << " " << order->occupy_vec.size();
            for (int i = 0; i < order->occupy_vec.size(); ++i) {
                int occupy_idx = order->occupy_vec[i];
                cout << " " << occupy_vec[occupy_idx]->machine_idx << " " << occupy_vec[occupy_idx]->time;
            }
        }
        cout << "\n";
    }
}