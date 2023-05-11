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
    /* Vector object to keep track of the starting, current and working solution as well as the improvement made on an iteration
     * the starting solution won't change and is only for comparison
     * the current solution is the solution that evolves at each iteration
     * the working solution is where the current solution is modified in its neighbourhood
     * the improvement is where the chosen next neighbour is stored */
    vector<int> starting_solution, current_solution, improvement, working_solution;
    long inital_score, current_score, best_improvement_score;

    /* PfspInstance to access score computation */
    PfspInstance instance;

    /* Flags to know when to stop the run or the iteration */
    bool stop_flag, improvement_flag;

    /* Pointer to the chosen pivoting rule */
    void (FlowshopInstance::*improvement_func)();

    /* Vector of the permutation functions through which we will iterate */
    vector<void (FlowshopInstance::*)()> permutation_functions;

    /* Permutation functions: they run through a specific neighbourhood */
    void exchange();
    void insert();
    void transpose();

    /* Pivoting rule functions */
    void first_improvement();
    void best_improvement();
public:
    FlowshopInstance(vector<int> &sol, PfspInstance pfspInstance, vector<string> parameters);
    ~FlowshopInstance();

    /* Improve goes from one neighbour to the next (depending on the neighbourhood and the pivoting rule */
    void improve();
    /* Run calls Improve until no more progress is made i.e. we have converged */
    void run();
    /* Perturbation */
    void perturbation(int nbrPerturbation);

    vector<int> getCurrentSolution();
    long getCurrentScore();
};


#endif //HEURISTIC_PROJECT1_FLOWSHOPINSTANCE_H
