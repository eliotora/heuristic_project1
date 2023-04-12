//
// Created by eliotora on 4/04/23.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include "permutations.h"
using namespace std;

Permutation::Permutation(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int> improv, PfspInstance instance, long int curr_score)) {
    this->sol = sol;
    this->currMod = sol;
    this->improvement = vector<int>(sol.size());
    this->stop = false;
    this->improvType = improvType;
    this->instance = instance;
    this->currentScore = instance.computeWT(this->sol);
}

Permutation::Permutation(vector<int> &sol, PfspInstance instance, bool (*improvType)(vector<int>, PfspInstance instance, long int curr_score), long score) {
    this->sol = sol;
    this->currMod = sol;
    this->improvement = vector<int>(sol.size());
    this->stop = false;
    this->improvType = improvType;
    this->instance = instance;
    this->currentScore = score;
}

Permutation::~Permutation() {}

void Permutation::printVector(vector<int> vec) {
    for (int item: vec) {
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
    this->currMod.insert(this->currMod.begin() + final, val);
}

bool Permutation::evalImprovement() {
    return this->improvType(this->currMod, this->instance, this->currentScore);
}