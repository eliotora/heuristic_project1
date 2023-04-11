//
// Created by eliot on 11-04-23.
//

#include "exchange.h"

vector<int> Exchange::generateExchange(vector<int> sol) {
    this->currMod = sol; //Exchange to evaluate

    for (int i=0; i < e.size(); i++) {
        for (int j=i+1; j < e.size(); j++) {
            if (this.stop) {
                this.improvement = this.currMod;
                break;
            }
            this->doPermutation(i, j);
            // Do something
            this.stop = this->evalImprovement();

            this.currMod = sol;
        }
        if (this.stop) break;
    }

    return this.improvement;
}

void generateExchanges(vector<int> sol) {
    vector<int> e = sol; //Exchange to evaluate

    for (int i=0; i < e.size(); i++) {
        for (int j=i+1; j < e.size(); j++) {
            doPermutation(i, j, e);
            // Do something

            e = sol;
        }
    }
}
