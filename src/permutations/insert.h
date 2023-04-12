//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_INSERT_H
#define HEURISTIC_PROJECT1_INSERT_H

#include "../permutations.h"

class Insert: public Permutation {
public:
    Insert(vector<int> &sol, PfspInstance instance,
           bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score));
    Insert(vector<int> &sol, PfspInstance instance,
           bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score), long int score);
    using Permutation::Permutation;
    vector<int> generateInsert(vector<int> &sol);
};


#endif //HEURISTIC_PROJECT1_INSERT_H
