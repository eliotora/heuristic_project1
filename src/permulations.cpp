//
// Created by eliotora on 4/04/23.
//
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printVector(vector<int> vec) {
    for (int item: vec) {
        cout << item << ", ";
    }
    cout << endl;
}

void doPermutation(int i, int j, vector<int> &sol) {
    int a = sol[i];
    sol[i] = sol[j];
    sol[j] = a;
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

void generateInserts(vector<int> sol) {
    vector<int> ins = sol;

    for (int i=0; i<sol.size(); i++) {
        for (int j=0; j <= sol.size(); j++) {
            if (i != j) {
                cout << i << ";" << j << endl;
                ins.insert(ins.begin() + j, ins[i]);
                ins.erase(ins.begin() + i);
                printVector(ins);
                ins = sol;
            }
        }
    }
}


int main() {
    vector<int> a;
    for (int i=1; i<5; ++i) {
        a.push_back(i);
    }
    generateInserts(a);
    cout << "Dafuk" << endl;
}