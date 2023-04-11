//
// Created by eliot on 11-04-23.
//

#include "insert.h"

vector<int> Insert::generateInsert() {
    this.currMod = sol;

    for (int i=0; i<sol.size(); i++) {
        for (int j=0; j <= sol.size(); j++) {
            if (this.stop) {
                this.improvement = this.currMod;
                break
            }
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                this->doInsert(i, j);
                // Do something
                this.stop = this->evalImprovement();

                this.currMod = sol;
            }
        }
        if (this.stop) break;
    }

    return this.improvement;
}

void generateInserts(vector<int> sol) {
    vector<int> ins = sol;

    for (int i=0; i<sol.size(); i++) {
        for (int j=0; j <= sol.size(); j++) {
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                doInsert(i, j, ins);
                // Do something


                ins = sol;
            }
        }
    }
}