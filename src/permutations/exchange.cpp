//
// Created by eliot on 11-04-23.
//

#include "exchange.h"
#include <iostream>


Exchange::Exchange(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long)): Permutation(sol, instance, improvType) {}

Exchange::Exchange(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance, long),
                   long score): Permutation(sol, instance, improvType, score) {}

vector<int> Exchange::generateExchange(vector<int> &sol) {
    this->currMod = sol; //Exchange to evaluate
    this->stop = false;
    for (int i=1; i < sol.size()-1; i++) {
        for (int j=i+1; j < sol.size()-1; j++) {
            this->currMod = sol;
            this->doPermutation(i, j);
            // Do something
            this->stop = this->evalImprovement();

            if (this->stop) {
                sol = this->currMod;
                printVector(sol);
                cout << "break" << endl;

                break;
            }
        }
        if (this->stop) break;
    }
    if (not stop) {
        cout << "No improvement in neighbourhood." << endl;
        this->improvement = sol;
    }
    return sol;
}

void generateExchanges(vector<int> sol) {
    vector<int> e = sol; //Exchange to evaluate

    for (int i=0; i < e.size(); i++) {
        for (int j=i+1; j < e.size(); j++) {
            //doPermutation(i, j, e);
            // Do something

            e = sol;
        }
    }
}
