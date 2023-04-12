//
// Created by eliotora on 12/04/23.
//

#ifndef HEURISTIC_PROJECT1_FLOWSHOPINSTANCE_H
#define HEURISTIC_PROJECT1_FLOWSHOPINSTANCE_H

#include <vector>
#include <string>
#include <iostream>
#include "pfspinstance.h"
#include "utils.h"


using namespace std;

class FlowshopInstance {
private:
    vector<int> starting_solution, current_solution, improvement, working_solution;
    long inital_score, current_score, best_improvement_score;
    PfspInstance instance;
    bool stop_flag, improvement_flag;
    void (FlowshopInstance::*improvement_func)();
    void (FlowshopInstance::*permutation_func)();
    void exchange();
    void insert();
    void transpose();
    void first_improvement();
    void best_improvement();
public:
    FlowshopInstance(vector<int> &sol, PfspInstance pfspInstance, vector<string> parameters);
    ~FlowshopInstance();
    void improve();
    void run();
    vector<int> getCurrentSolution();
    long getCurrentScore();
};


#endif //HEURISTIC_PROJECT1_FLOWSHOPINSTANCE_H
