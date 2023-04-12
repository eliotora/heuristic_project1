//
// Created by eliot on 11-04-23.
//

#include "transpose.h"
#include <iostream>

Transpose::Transpose(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long)):Permutation(sol, instance, improvType) {}

Transpose::Transpose(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long),
                     long score): Permutation(sol, instance, improvType, score) {}

vector<int> Transpose::generateTranspose(vector<int> &sol) {
    this->currMod = sol; //Transpose to evaluate
    this->stop = false;
    // Every other permutation one by one
    for (int i = 1; i < sol.size()-1 ; i++) {
        if (this->stop) {
            this->improvement = this->currMod;
            cout << "break" << endl;
            break;
        }
        this->currMod = sol;
        this->doPermutation(i, i+1);
        // Do something
        this->stop = this->evalImprovement();

    }
    if (not this->stop) this->improvement = sol;
    return this->improvement;
}

void generateTransposes(vector<int> sol) {
    vector<int> t = sol; //Transpose to evaluate

    // Every other permutation one by one
    for (int i = 0; i < t.size() ; i++) {
        //doPermutation(i, i+1, t);
        // Do something

        t = sol;
    }
}