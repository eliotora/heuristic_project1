/***************************************************************************
 *   Copyright (C) 2012 by Jérémie Dubois-Lacoste   *
 *   jeremie.dl@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <filesystem>
#include <algorithm>
#include "pfspinstance.h"
#include "flowshopinstance.h"
#include "ILS.h"
#include "MA.h"

using namespace std;
using namespace std::chrono;

int findMax(vector<float> & vec)
{
    int res = 0;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[res]) res = i;
    return res;
}

/* Generate the simplified RZ heuristic starting solution */
void simpRZsolution(int nbJobs, vector<int> & sol, PfspInstance instance)
{
    // Phase 1: Order by Di
    vector<float> weightedSumProcTime(nbJobs+1, 0);
    int nbMac = instance.getNbMac();

    /* find the weighted sum of process time of each job */
    for (int i = nbJobs; i >= 1; --i)
    {
        long sumTime = 0;
        /* find the total process time of the job */
        for (int j = nbMac; j>=1; --j) sumTime += instance.getTime(i,j);

        weightedSumProcTime[i] = ((float) sumTime)/(float) instance.getPriority(i);

    }


    // Phase 2: for each job find the best position to insert
    int remainingJobs = nbJobs;
    int posMax;
    for (int i = nbJobs; i >= 1; --i)
    {
        posMax = findMax(weightedSumProcTime);
        sol[remainingJobs--] = posMax;
        weightedSumProcTime[posMax] = 0;
    }
}

int generateRndPosition(int min, int max)
{
  return ( rand() % max + min );
}

/* Fill the solution with numbers between 1 and nbJobs, shuffled */
vector<int> randomPermutation(int nbJobs)
{
    vector<int> sol(nbJobs+1);
    vector<bool> alreadyTaken(nbJobs+1, false); // nbJobs elements with value false
    vector<int > choosenNumber(nbJobs+1, 0);

    int nbj;
    int rnd, i, j, nbFalse;

    nbj = 0;
    for (i = nbJobs; i >= 1; --i)
    {
        rnd = generateRndPosition(1, i);
        nbFalse = 0;

        /* find the rndth cell with value = false : */
        for (j = 1; nbFalse < rnd; ++j)
            if ( ! alreadyTaken[j] )
                ++nbFalse;
        --j;

        sol[j] = i;

        ++nbj;
        choosenNumber[nbj] = j;

        alreadyTaken[j] = true;
    }
    return sol;
}

/* Create an output file for the iteration */
void open_file(int argc, char **&argv, fstream &file) {
    char name[30] = "";
    for (int i=1; i < argc-1; i++) {
        strcat(name,argv[i]);
    }
    file.open(name, ios::trunc|ios::out);
}

vector<string> readDirectory(string path) {
    vector<string> names = vector<string>();
    for (const auto& entry : filesystem::directory_iterator(path)) {
        names.emplace_back(entry.path().string().c_str());
    }
    sort(names.begin(), names.end());
    return names;
}

vector<string> parseArg(int argc, char **argv) {
    vector<string> parameter = vector<string>();
    bool all_good = true;
    if (argc < 2) all_good = false;
    else parameter.emplace_back((string)argv[1]);
    if (all_good and argc >= 5 and (string)argv[1] == "--ii") {
        cout << "ii" << endl;
        if ((string)argv[3] == "--exchange" or (string)argv[3] == "--transpose" or (string)argv[3] == "--insert") parameter.emplace_back((string)argv[3]);
        if ((string)argv[2] == "--first" or (string)argv[2] == "--best") parameter.emplace_back((string)argv[2]);
        if ((string)argv[4] == "--srz" or (string)argv[4] == "--rand") parameter.emplace_back((string)argv[4]);
        if (parameter.size() != 4) all_good = false;
    } else if (all_good and argc >= 3 and (string)argv[1] == "--vnd") {
        cout << "vnd" << endl;
        if ((string)argv[2] == "--tie" or (string)argv[2] == "--tei" or argv[3]) parameter.emplace_back((string)argv[3]);
        parameter.emplace_back("--first");
        parameter.emplace_back("--srz");
        if (parameter.size() != 4) all_good = false;
    } else if (all_good and argc >= 2 and (string)argv[1] == "--ils") {
        cout << "ils" << endl;
        parameter.emplace_back("--tie");
        parameter.emplace_back("--first");
        parameter.emplace_back("--srz");
    } else if (all_good and argc >= 2 and (string)argv[1] == "--ma") {
        cout << "ma" << endl;
    }
    else all_good = false;

    if (!all_good) {
        cout
        << "Usage: ./pfspwt --ii --first|--best --exchange|--transpose|--insert --srz|--rand" << endl
        << "or ./pfspwt --vnd --tei|tie" << endl
        << "or ./pfspwt --ils" << endl;
        std::exit(1);
    }
    return parameter;
}

/***********************************************************************/

int main(int argc, char **argv)
{
    cout << endl;
    vector<string> parameters = parseArg(argc, argv);
    // Prepare the output file
    string path = "PFSP_instances";
    fstream fout;
    open_file(argc, argv, fout);

    // Instances to do
    vector<string> instances = readDirectory(path);
    instances = {(string)argv[argc -1]};
    //instances = {"PFSP_instances/DD_Ta081.txt"};

    // Number of runs to do on each instances
    int run_nb = 5;
    //int run_nb = stoi((string)argv[argc - 1]);

    // Start to iterate the run on each instance file
    for (const basic_string<char>& entry : instances) {
        cout << entry << endl;
        /* Create instance object */
        PfspInstance instance;

        if (!instance.readDataFromFile(const_cast<char *>(entry.c_str()))) {
            return 1;
        }

        // Loop 5 times through the full run
        for (int ite = 0; ite < run_nb; ite++) {
            cout << "Run: " << ite+1 << endl;
            /* Start the clock */
            auto start = high_resolution_clock::now();

            /* initialize random seed: */
            srand(time(NULL));




            /* Create a vector of int to represent the solution
               WARNING: By convention, we store the jobs starting from index 1,
                        thus the size nbJob + 1. */
            vector<int> solution(instance.getNbJob() + 1);

            /* Prepare the input for the instance */

            int time;
            if (instance.getNbJob() == 50) time = 225; //sec
            else time = 6205; //sec
            long score = 0;
            if (parameters[3] == "--rand") {
                /* Fill the vector with a random permutation */
                solution = randomPermutation(instance.getNbJob());
            } else if (parameters[3] == "--srz") {
                /* Fill the vector with the simplified RZ heuristic solution */
                simpRZsolution(instance.getNbJob(), solution, instance);
            }
            if (parameters[0] == "--ils") {
                parameters[0] = "--vnd";
                ILS ils_instance = ILS(solution, instance, parameters, time);
                ils_instance.run();

                solution = ils_instance.getCurrentSolution();
                score = ils_instance.getCurrentScore();
                parameters[0] = "--ils";
            } else if (parameters[0] == "--ma") {
                vector<vector<int>> rand_population;
                vector<int> rand_solution;
                for (int i=0; i < 100; i++) {
                    rand_solution = randomPermutation(instance.getNbJob());
                    rand_population.emplace_back(rand_solution);
                }
                MA ma_instance = MA(rand_population, instance, time/10);
                ma_instance.run();

                solution = ma_instance.get_best_solution();
                score = ma_instance.get_best_score();
            }
            else {
                /* Create instance object */
                FlowshopInstance flowshopInstance = FlowshopInstance(solution, instance, parameters);

                /* Start the run */
                flowshopInstance.run();
                solution = flowshopInstance.getCurrentSolution();
                score = flowshopInstance.getCurrentScore();
            }

            /* Stop the clock and get the duration of the run */
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            /* Compute the WT of this solution */
            /*cout << "Total weighted tardiness: " << score << endl;*/
//            cout << "Total run time: " << duration.count() << " microseconds" << endl;

            // Output result in the file

            fout << entry << ", " << score << ", " << duration.count() << "\n";
        }
    }
    return 0;
}
