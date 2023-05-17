//
// Created by eliotora on 12/05/23.
//
#include "flowshopinstance.h"
#include <algorithm>
#include <chrono>

#ifndef HEURISTIC_PROJECT1_MA_H
#define HEURISTIC_PROJECT1_MA_H


class MA {
private:
    long maxTime;
    float mutation_prob = 0.05;
    vector<string> parameters;
    PfspInstance pfspInstance;
    vector<FlowshopInstance> sp, spr, spm; // starting population, starting population recombination, starting population mutated

    void recombination(); // Create children and apply selection
    vector<int> cross_over_operator(vector<int> genome1, vector<int> genome2);
    void mutation();
public:
    MA(vector<vector<int>> start_pop, PfspInstance instance, long time);
    ~MA();
    void run();
    vector<int> get_best_solution();
    long get_best_score();
    static bool compFlowInst(FlowshopInstance &sol1, FlowshopInstance &sol2);
};

#endif //HEURISTIC_PROJECT1_MA_H
