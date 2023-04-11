//
// Created by eliot on 11-04-23.
//

#ifndef HEURISTIC_PROJECT1_PERMUTATIONS_H
#define HEURISTIC_PROJECT1_PERMUTATIONS_H

#include <vector>

using namespace std;

class Permutation{
private:
    vector<int> sol, currMod, improvement;
    bool stop;
    void (*improvType)(vector<int> improv);

public:
    Permutation(vector<int> &sol, void (*improvType)(vector<int> improv));
    ~Permutation();
    void printImprovement();
    void doPermutation(int i, int j);
    void doInsert(int initial, int final);
    bool evalImprovement();
};

#endif //HEURISTIC_PROJECT1_PERMUTATIONS_H
