//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_EXCHANGE_H
#define HEURISTIC_PROJECT1_EXCHANGE_H

#include "../permutations.h"

class Exchange: public Permutation {
public:
    Exchange(vector<int> &sol, PfspInstance instance,
             bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score));
    Exchange(vector<int> &sol, PfspInstance instance,
             bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score), long int score);
    using Permutation::Permutation;
    vector<int> generateExchange(vector<int> &sol);
};


#endif //HEURISTIC_PROJECT1_EXCHANGE_H
