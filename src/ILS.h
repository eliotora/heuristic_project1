//
// Created by eliotora on 11/05/23.
//

#include "flowshopinstance.h"

#ifndef HEURISTIC_PROJECT1_ILS_H
#define HEURISTIC_PROJECT1_ILS_H


class ILS {
private:
    FlowshopInstance working_instance;
    /* Parameters */
    int gamma = 4; // TODO:perturbation_nbr to adjust; (set to 2 see (ref PanRuiz2012))
    float lambda = 4.0; // TODO:temperature parameter to ajdust; (set to 4.0 see (ref PanRuiz2012))
    float temp;
    long maxTime; // In microsec

    /* Solution given at creation */
    vector<int> current_solution, best_so_far_solution;
    long current_score, best_so_far_score;

    /* Stored Memory of best solutions */
    vector<vector<int>> memory;
public:
    ILS(vector<int>& s, PfspInstance pfspInstance, vector<string>& parameters, long time);
    ~ILS();
    void run();
    bool termination_condition();
    void acceptance_criterion();
    vector<int> getCurrentSolution();
    long getCurrentScore();
};


#endif //HEURISTIC_PROJECT1_ILS_H
