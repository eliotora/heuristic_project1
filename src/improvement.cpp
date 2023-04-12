//
// Created by eliotora on 5/04/23.
//

#include "improvement.h"
#include <iostream>

bool firstImprovement(vector<int> sol, PfspInstance instance, long int curr_score) {
    cout << "Solution received: ";
    for (int job: sol) cout << job << ", ";
    long int new_score = instance.computeWT(sol);
    cout << endl << "New score: " << new_score << "; result: " << (bool)(new_score < curr_score) << endl;
    return new_score < curr_score;
}