//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_PERMUTATIONS_H
#define HEURISTIC_PROJECT1_PERMUTATIONS_H

#include <vector>
#include "pfspinstance.h"

using namespace std;

class Permutation{
public:
    vector<int> sol, currMod, improvement;
    bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score);
    bool stop;
    long int currentScore;
    PfspInstance instance;
    Permutation(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score));
    Permutation(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score), long int score);
    ~Permutation();
    void printVector(vector<int> vec);
    void doPermutation(int i, int j);
    void doInsert(int initial, int final);
    bool evalImprovement();
};

#endif //HEURISTIC_PROJECT1_PERMUTATIONS_H
