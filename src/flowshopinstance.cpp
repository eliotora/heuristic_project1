//
// Created by eliotora on 12/04/23.
//

#include "flowshopinstance.h"

FlowshopInstance::FlowshopInstance(vector<int> &sol, PfspInstance pfspInstance, vector<string> parameters) {
    //cout << "Creating Instance" << endl;
    /* Initialise the solution attributes */
    starting_solution = sol;
    current_solution = sol;
    improvement = sol;
    working_solution = sol;
    instance = pfspInstance;
    inital_score = instance.computeWT(starting_solution);
    current_score = inital_score;
    best_improvement_score = inital_score;
    /* Depending on the parameters:
     * Add only one permutation function to the vector if --ii is the first parameter
     * Chosen permutation function depend on the second parameter
     *
     * Add the three permutation functions to the vector if --vnd is the first parameter
     * Order of the functions depends on the second input
     * */
    if (parameters[0] == "--ii") {
        if (parameters[1] == "--exchange") permutation_functions.push_back(&FlowshopInstance::exchange);
        else if (parameters[1] == "--insert") permutation_functions.push_back(&FlowshopInstance::insert);
        else if (parameters[1] == "--transpose") permutation_functions.push_back(&FlowshopInstance::transpose);
    }
    if (parameters[0] == "--vnd") {
        permutation_functions.push_back(&FlowshopInstance::transpose);
        if (parameters[1] == "--tei") {
            permutation_functions.push_back(&FlowshopInstance::exchange);
            permutation_functions.push_back(&FlowshopInstance::insert);
        }
        else if (parameters[1] == "--tie") {
            permutation_functions.push_back(&FlowshopInstance::insert);
            permutation_functions.push_back(&FlowshopInstance::exchange);
        }
    }
    /* Select the pivoting rule function depending on the third input */
    if (parameters[2] == "--first") improvement_func = &FlowshopInstance::first_improvement;
    else if (parameters[2] == "--best") improvement_func = &FlowshopInstance::best_improvement;
    //cout << "Instance created, initial score: " << inital_score << endl;
}

FlowshopInstance::~FlowshopInstance() {}

/* Run the improvement method until no more progress is made i.e. the improvement flag become false */
void FlowshopInstance::run() {
    improvement_flag = true;
    //cout << "Started run" << endl;
    while (improvement_flag) {
        improve();
    }
}

/* Run through each neighbourhood of the permutation vector until the stop flag becomes true */
void FlowshopInstance::improve() {
    improvement_flag = false;
    for (auto permutation_f: permutation_functions) {
        stop_flag = false;
        (this->*permutation_f)();
        if (stop_flag) break;
    }

    /* Accept the improvement */
    if (improvement_flag) {
        current_solution = improvement;
        current_score = best_improvement_score;
    }
}

void FlowshopInstance::insert() {
    // Reset the working solution and the flag
    working_solution = current_solution;
    stop_flag = false;

    for (int i=1; i<starting_solution.size()-1; i++) {
        for (int j=1; j <= starting_solution.size(); j++) {
            if (i == j) continue;
            if (j - i > 1 or i - j > 1) {
                // Reset the working solution
                working_solution = current_solution;
                doInsert(i, j, working_solution);

                // Call the pivoting rule to know if we have improved and if we need to stop
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
    // Reset the working solution and the flag
    working_solution = current_solution; //Exchange to evaluate
    stop_flag = false;
    for (int i=1; i < starting_solution.size()-1; i++) {
        for (int j=i+1; j < starting_solution.size()-1; j++) {
            // Reset the working solution and the flag
            working_solution = current_solution;
            doPermutation(i, j, working_solution);

            // Call the pivoting rule to know if we have improved and if we need to stop
            (this->*improvement_func)();

            if (stop_flag) {
                break;
            }
        }
        if (stop_flag) break;
    }
}

void FlowshopInstance::transpose() {
    // Reset the working solution and the flag
    working_solution = current_solution; //Transpose to evaluate
    stop_flag = false;
    // Every other permutation one by one
    for (int i = 1; i < starting_solution.size()-1 ; i++) {
        if (stop_flag) {
            break;
        }
        // Reset the working solution and the flag
        working_solution = current_solution;
        doPermutation(i, i+1, working_solution);

        // Call the pivoting rule to know if we have improved and if we need to stop
        (this->*improvement_func)();
    }
}

/* Flip the stop flag and the improvement flag if any improvement is made */
void FlowshopInstance::first_improvement() {
    long new_score = instance.computeWT(working_solution);
    if (new_score < current_score){
        best_improvement_score = new_score;
        improvement = working_solution;
        stop_flag = true;
        improvement_flag = true;
    }
}

/* Flip the improvement flag if any improvement is made but never the stop flag so that we can see the full neighbourhood */
void FlowshopInstance::best_improvement() {
    long new_score = instance.computeWT(working_solution);
    if (new_score < best_improvement_score) {
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


/* ILS part:
 * Perturbation implementation via multiple random insertions */
void FlowshopInstance::perturbation(int nbrPerturbation) {
    for (int _ = 0; _ < 2; _++) {
        int i = rand() % starting_solution.size();
        int j = rand() % starting_solution.size();
        while (j==i) j = rand() % starting_solution.size();
        doInsert(i, j, current_solution);
    }
}