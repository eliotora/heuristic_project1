//
// Created by eliotora on 12/04/23.
//

#include "utils.h"

void doPermutation(int i, int j, vector<int> &vec) {
    int a = vec[i];
    vec[i] = vec[j];
    vec[j] = a;
}

void doInsert(int initial, int final, vector<int> &vec) {
    int val = vec[initial];
    vec.erase(vec.begin() + initial);
    if (final > initial) {
        final--;
    }
    vec.insert(vec.begin() + final, val);
}

void printVector(vector<int> vec) {
    for (int item: vec) {
        cout << item << ", ";
    }
    cout << endl;
}