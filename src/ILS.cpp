//
// Created by eliotora on 11/05/23.
//

#include "ILS.h"
#include <random>
#include <chrono>

ILS::ILS(vector<int>& s, PfspInstance pfspInstance, vector<string>& parameters, long time):
working_instance(s, pfspInstance, parameters) {
    best_so_far_solution = s;
    current_solution = s;
    // Initialise temperature
    temp = lambda * (pfspInstance.getTotalJobTime())/(10*pfspInstance.getNbJob()*pfspInstance.getNbMac());
    maxTime = time;
}

ILS::~ILS() {}

void ILS::run() {
    /*
     * Main function of the ILS method
     */
    auto begin = std::chrono::high_resolution_clock::now();
    working_instance.run();
    current_solution = working_instance.getCurrentSolution();
    current_score = working_instance.getCurrentScore();
    best_so_far_solution = current_solution;
    best_so_far_score = current_score;
    do{
        working_instance.perturbation(gamma);
        working_instance.run();
        acceptance_criterion();
//        cout << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count() << "seconds over " << maxTime << " seconds " << endl;
    } while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count() < maxTime);
}

// Simulated annealing acceptance criterion (ref PanRuiz2012)
void ILS::acceptance_criterion() {
    // Decide whether the new solution is accepted or not
    if (working_instance.getCurrentScore() < current_score) {
        // If the score is better than the score of current solution we accept
        current_solution = working_instance.getCurrentSolution();
        current_score = working_instance.getCurrentScore();
        if (current_score < best_so_far_score) {
            // If the score is better than the score of best solution we memorise
            best_so_far_solution = current_solution;
            best_so_far_score = current_score;
        }
    } else if (rand()/RAND_MAX <= exp((current_score - working_instance.getCurrentScore())/temp)) {
        current_solution = working_instance.getCurrentSolution();
        current_score = working_instance.getCurrentScore();
    }
}

vector<int> ILS::getCurrentSolution() {
    return best_so_far_solution;
}

long ILS::getCurrentScore() {
    return best_so_far_score;
}