//
// Created by eliotora on 12/04/23.
//

#include "utils.h"

/* Permute the i_th element and the j_th element in the vector vec */
void doPermutation(int i, int j, vector<int> &vec) {
    int a = vec[i];
    vec[i] = vec[j];
    vec[j] = a;
}

/* Move the element in the initial position to the final position in the vector vec */
void doInsert(int initial, int final, vector<int> &vec) {
    int val = vec[initial];
    vec.erase(vec.begin() + initial);
    if (final > initial) {
        final--;
    }
    vec.insert(vec.begin() + final, val);
}

/* Output the vector (for debugging) */
void printVector(vector<int> vec) {
    for (int item: vec) {
        cout << item << ", ";
    }
    cout << endl;
}