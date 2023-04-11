//
// Created by eliot on 11-04-23.
//

#include "transpose.h"

vector<int> Transpose::generateTranspose(vector<int> sol) {
    this->currMod = sol; //Transpose to evaluate

    // Every other permutation one by one
    for (int i = 0; i < t.size() ; i++) {
        if (this->stop) {
            this.improvement = this.currMod;
            break;
        }
        this->doPermutation(i, i+1);
        // Do something
        this->stop = this->evalImprovement();

        this.currMod = sol;
    }

    return this.improvement;
}

void generateTransposes(vector<int> sol) {
    vector<int> t = sol; //Transpose to evaluate

    // Every other permutation one by one
    for (int i = 0; i < t.size() ; i++) {
        doPermutation(i, i+1, t);
        // Do something

        t = sol;
    }
}