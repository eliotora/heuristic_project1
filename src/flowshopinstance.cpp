//
// Created by eliotora on 12/04/23.
//

#include "flowshopinstance.h"

FlowshopInstance::FlowshopInstance(vector<int> &sol, PfspInstance pfspInstance, vector<string> parameters) {
    /*cout << "Creating Instance" << endl;*/
    starting_solution = sol;
    current_solution = sol;
    improvement = sol;
    working_solution = sol;
    instance = pfspInstance;
    inital_score = instance.computeWT(starting_solution);
    current_score = inital_score;
    best_improvement_score = inital_score;
    if (parameters[0] == "--exchange") permutation_func = &FlowshopInstance::exchange;
    else if (parameters[0] == "--insert") permutation_func = &FlowshopInstance::insert;
    else if (parameters[0] == "--transpose") permutation_func = &FlowshopInstance::transpose;
    if (parameters[1] == "--first") improvement_func = &FlowshopInstance::first_improvement;
    else if (parameters[1] == "--best") improvement_func = &FlowshopInstance::best_improvement;
    /*cout << "Instance created, initial score: " << inital_score << endl;*/
}

FlowshopInstance::~FlowshopInstance() {}

void FlowshopInstance::run() {
    improvement_flag = true;
    int i = 1;
    while (improvement_flag) {
        /*cout << "-------------------------------------------------------------" << endl;
        cout << "Iteration: " << i++ << endl;*/
        improve();
    }
}

void FlowshopInstance::improve() {
    improvement_flag = false;
    (this->*permutation_func)();
    if (improvement_flag) {
        current_solution = improvement;
        current_score = best_improvement_score;
    }
}

void FlowshopInstance::insert() {
    working_solution = current_solution;
    stop_flag = false;

    for (int i=1; i<starting_solution.size()-1; i++) {
        for (int j=1; j <= starting_solution.size(); j++) {
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                working_solution = current_solution;
                doInsert(i, j, working_solution);
                // Do something
                (this->*improvement_func)();
            }
            if (stop_flag) {
                break;
            }
        }
        if (stop_flag) break;
    }
}

void FlowshopInstance::exchange() {
    working_solution = current_solution; //Exchange to evaluate
    stop_flag = false;
    for (int i=1; i < starting_solution.size()-1; i++) {
        for (int j=i+1; j < starting_solution.size()-1; j++) {
            working_solution = current_solution;
            doPermutation(i, j, working_solution);
            // Do something
            (this->*improvement_func)();

            if (stop_flag) {
                break;
            }
        }
        if (stop_flag) break;
    }
}

void FlowshopInstance::transpose() {
    working_solution = current_solution; //Transpose to evaluate
    stop_flag = false;
    // Every other permutation one by one
    for (int i = 1; i < starting_solution.size()-1 ; i++) {
        if (stop_flag) {
            break;
        }
        working_solution = current_solution;
        doPermutation(i, i+1, working_solution);
        // Do something
        (this->*improvement_func)();

    }
}

void FlowshopInstance::first_improvement() {
    long new_score = instance.computeWT(working_solution);
    if (new_score < current_score){
        /*cout << "Evaluating improvement: " << new_score << " vs. " << current_score << " for: " << endl;
        printVector(working_solution);*/
        best_improvement_score = new_score;
        improvement = working_solution;
        stop_flag = true;
        improvement_flag = true;
    }
}

void FlowshopInstance::best_improvement() {
    long new_score = instance.computeWT(working_solution);
    if (new_score < best_improvement_score) {
        /*cout << "Evaluating improvement: " << new_score << " vs. " << current_score << " for: " << endl;
        printVector(working_solution);*/
        best_improvement_score = new_score;
        improvement = working_solution;
        improvement_flag = true;
    }
}

vector<int> FlowshopInstance::getCurrentSolution() {
    return current_solution;
}

long FlowshopInstance::getCurrentScore() {
    return current_score;
}
