//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_TRANSPOSE_H
#define HEURISTIC_PROJECT1_TRANSPOSE_H

#include "../permutations.h"

class Transpose: public Permutation {
private:


public:
    Transpose(vector<int> &sol, PfspInstance instance,
              bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score));
    Transpose(vector<int> &sol, PfspInstance instance,
              bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score), long int score);
    using Permutation::Permutation;
    vector<int> generateTranspose(vector<int> &sol);
};


#endif //HEURISTIC_PROJECT1_TRANSPOSE_H
