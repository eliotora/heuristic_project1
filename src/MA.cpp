//
// Created by eliotora on 12/05/23.
//

#include "MA.h"

MA::MA(vector<vector<int>> start_pop, PfspInstance instance, long time) {
    maxTime = time;
    pfspInstance = instance;
    parameters = {"--vnd","--tie","--first"};
    for (auto solution: start_pop) {
        sp.emplace_back(FlowshopInstance(solution, instance, parameters));
    }
}

MA::~MA() {}

void MA::recombination() {
    int a = 1;
    for (int i=0; i<sp.size(); i++) {
        // Two different random positions in the population
        int p1 = rand() % sp.size();
        int p2 = rand() % sp.size();
        while (p1 == p2) p2 = rand() % sp.size();

        // The genome of the parents
        vector<int> genome1 = sp[p1].getCurrentSolution();
        vector<int> genome2 = sp[p2].getCurrentSolution();

        // Cross-over and creation of the child
        vector<int> child_genome(pfspInstance.getNbJob()+1);
        child_genome = cross_over_operator(genome1, genome2);
        FlowshopInstance child = FlowshopInstance(child_genome, pfspInstance, parameters);
        child.run(); // subsidiary local search on child

        // Keep only the 2 best of the two parents plus the child
        if (child.getCurrentScore() <= sp[p1].getCurrentScore() or
            child.getCurrentScore() <= sp[p2].getCurrentScore()) {
            if (sp[p1].getCurrentScore() > sp[p2].getCurrentScore()) sp.erase(sp.begin() + p2);
            else sp.erase(sp.begin() + p1);
            sp.emplace_back(child);
        }
    }
}

vector<int> MA::cross_over_operator(vector<int> genome1, vector<int> genome2) {
    int cut = random() % genome1.size(); // Randomly choose the position of the cut
    vector<int> g1 = vector<int>(genome1.begin(), genome1.begin()+cut); // First part of the child's genome
    vector<int> g2 = vector<int>(genome2.begin() + cut, genome2.end()); // Second part of the child's genome


    vector<int> repairs = vector<int>(genome2.begin(), genome2.begin()+cut); // Part of the genome2 that won't be in the child


    for (int gene: g1) { // remove from g2 and repairs the genes that are in g1
        auto it = find(g2.begin(), g2.end(), gene);
        if( it != g2.end()) g2.erase(it);

        auto it2 = find(repairs.begin(), repairs.end(), gene);
        if(it2 != repairs.end()) repairs.erase(it2);
    }

    // concatenate g1, g2 and repairs
    g1.insert(g1.end(), g2.begin(), g2.end());
    g1.insert(g1.end(), repairs.begin(), repairs.end());
    return g1;
}

void MA::mutation() {
    for (auto elem: sp) {
        if (rand()/RAND_MAX < mutation_prob) {
            elem.perturbation(2); // Mutation consists of two random insertion move
            elem.run();
        }
    }
}

void MA::run() {
    auto begin = std::chrono::high_resolution_clock::now();
    for (auto elem: sp) elem.run();
    do {
        recombination();
        mutation();
    } while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin).count() < maxTime);
}

bool MA::compFlowInst(FlowshopInstance &sol1, FlowshopInstance &sol2) {return sol1.getCurrentScore() < sol2.getCurrentScore();}

vector<int> MA::get_best_solution() {
    return min_element(sp.begin(), sp.end(), compFlowInst)->getCurrentSolution();
}

long MA::get_best_score() {
    return min_element(sp.begin(), sp.end(), compFlowInst)->getCurrentScore();
}