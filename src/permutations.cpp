//
// Created by eliotora on 4/04/23.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include "permutations.h"
using namespace std;

Permutation::Permutation(vector<int> &sol, void (*improvType)(vector<int> improv)) {
    this->sol = sol;
    this->currMod = sol;
    this->improvement = vector<int>(sol.size());
    this->stop = false;
    this->improvType = improvType;
}
Permutation::~Permutation() {}

void Permutation::printImprovement() {
    for (int item: this->improvement) {
        cout << item << ", ";
    }
    cout << endl;
}

void Permutation::doPermutation(int i, int j) {
    int a = this->currMod[i];
    this->currMod[i] = this->currMod[j];
    this->currMod[j] = a;
}

void Permutation::doInsert(int initial, int final) {
    int val = this->currMod[initial];
    this->currMod.erase(this->currMod.begin() + initial);
    if (final > initial) {
        final--;
    }
    this->currMod.insert(vec.begin() + final, val);
}

bool Permutation::evalImprovement() {
    return this->improvType(this->currMod);
}





int main() {
    vector<int> a, b;
    for (int i=1; i<6; ++i) {
        a.push_back(i);
    }
    b = a;
    /*doInsert(0,1,b);
    printVector(b);*/
    generateInserts(a);
}