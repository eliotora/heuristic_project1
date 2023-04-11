//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_TRANSPOSE_H
#define HEURISTIC_PROJECT1_TRANSPOSE_H

#include "permutations.h"

class Transpose: Permutation {
private:


public:
    using Permutation::Permutation;
    vector<int> generateTranspose(vector<int> sol);
};


#endif //HEURISTIC_PROJECT1_TRANSPOSE_H
