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
#include "pfspinstance.h"
#include "flowshopinstance.h"

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
void randomPermutation(int nbJobs, vector< int > & sol)
{
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
}

/* Create an output file for the iteration */
void open_file(char **&argv, fstream &file) {
    char name[30] = "";
    strcat(name,argv[1]);
    strcat(name,argv[2]);
    strcat(name, argv[3]);
    strcat(name, argv[4]);
    file.open(name, ios::trunc|ios::out);
}

/***********************************************************************/

int main(int argc, char **argv)
{
    // Prepare the output file
    string path = "PFSP_instances";
    fstream fout;
    open_file(argv, fout);

    if (argc < 5) {
        cout
                << "Usage: ./pfspwt --ii --first|--best --exchange|--transpose|--insert --srz|--rand"
                << endl
                << "or ./pfspwt --vnd --first|--best --tei|tie --srz|--rand"
                << endl;
        return 0;
    }

    // Start to iterate the run on each instance file
    for (const auto& entry : filesystem::directory_iterator(path)) {
        cout << entry << endl;
        /* Create instance object */
        PfspInstance instance;

        /* Read data from file */
        if (!instance.readDataFromFile(const_cast<char *>(entry.path().string().c_str()))) {
            return 1;
        }

        // Loop 5 times through the full run
        for (int ite = 0; ite < 5; ite++) {

            /* Start the clock */
            auto start = high_resolution_clock::now();

            /* initialize random seed: */
            srand(time(NULL));




            /* Create a vector of int to represent the solution
               WARNING: By convention, we store the jobs starting from index 1,
                        thus the size nbJob + 1. */
            vector<int> solution(instance.getNbJob() + 1);

            string s = argv[4];
            if (s == "--rand") {
                /* Fill the vector with a random permutation */
                randomPermutation(instance.getNbJob(), solution);
            } else if (s == "--srz") {
                /* Fill the vector with the simplified RZ heuristic solution */
                simpRZsolution(instance.getNbJob(), solution, instance);
            }

            /* Prepare the input for the instance */
            vector<string> parameters(3);
            parameters[0] = argv[1];
            parameters[1] = argv[3];
            parameters[2] = argv[2];

            /* Create instance object */
            FlowshopInstance flowshopInstance = FlowshopInstance(solution, instance, parameters);

            /* Start the run */
            flowshopInstance.run();

            solution = flowshopInstance.getCurrentSolution();

            /* Stop the clock and get the duration of the run */
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            /* Compute the WT of this solution */
            /*cout << "Total weighted tardiness: " << flowshopInstance.getCurrentScore() << endl;
            cout << "Total run time: " << duration.count() << " microseconds" << endl;*/

            // Output result in the file
            fout << entry << ", " << flowshopInstance.getCurrentScore() << ", " << duration.count() << "\n";
        }
    }
    return 0;
}
