//
// Created by eliot on 11-04-23.
//

#include "insert.h"
#include <iostream>

Insert::Insert(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long)): Permutation(sol, instance, improvType) {}
Insert::Insert(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long),
               long score): Permutation(sol, instance, improvType, score) {}

vector<int> Insert::generateInsert(vector<int>& sol) {
    this->currMod = sol;
    stop = false;

    for (int i=1; i<sol.size()-1; i++) {
        for (int j=1; j <= sol.size(); j++) {
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                this->currMod = sol;
                this->doInsert(i, j);
                // Do something
                this->stop = this->evalImprovement();
                printVector(currMod);
            }
            if (this->stop) {
                this->improvement = this->currMod;
                cout << "break" << endl;

                break;
            }
        }
        if (this->stop) break;
    }
    if (not stop) improvement = sol;
    return this->improvement;
}

void generateInserts(vector<int> sol) {
    vector<int> ins = sol;

    for (int i=0; i<sol.size(); i++) {
        for (int j=0; j <= sol.size(); j++) {
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                //doInsert(i, j, ins);
                // Do something


                ins = sol;
            }
        }
    }
}