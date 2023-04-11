//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_EXCHANGE_H
#define HEURISTIC_PROJECT1_EXCHANGE_H

#include "permutations.h"

class Exchange: Permutation {
public:
    using Permutation::Permutation;
    vector<int> generateExchange(vector<int> sol);
};


#endif //HEURISTIC_PROJECT1_EXCHANGE_H
