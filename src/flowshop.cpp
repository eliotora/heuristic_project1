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
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include "pfspinstance.h"
#include "permutations.h"
#include "permutations/transpose.h"
#include "permutations/exchange.h"
#include "permutations/insert.h"
#include "improvement.h"

using namespace std;

int findMax(vector<float> & vec)
{
    int res = 0;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[res]) res = i;
    return res;
}


void simpRZsolution(int nbJobs, vector<int> & sol, PfspInstance instance)
{
    // Phase 1: Order by Di
    vector<float> weightedSumProcTime(nbJobs+1, 0);
    int nbMac = instance.getNbMac();

    /* find the weighted sum of process time of each job */
    for (int i = nbJobs; i >= 1; --i)
    {
        int sumTime = 0;
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

/***********************************************************************/

int main(int argc, char **argv)
{
    int i;
    long int WeightedSumCompletionTimes;


    if (argc == 1)
    {
        cout << "Usage: ./flowshopWCT <instance_file>" << endl;
        return 0;
    }

    /* initialize random seed: */
    srand ( time(NULL) );

    /* Create instance object */
    PfspInstance instance;

    /* Read data from file */
    if (! instance.readDataFromFile(argv[1]) )
        return 1;
    /* Create a vector of int to represent the solution
       WARNING: By convention, we store the jobs starting from index 1,
                thus the size nbJob + 1. */
    vector< int > solution ( instance.getNbJob()+ 1 );
    string s = argv[2];
    cout << s << endl;
    if (s == "--rand")
    {
        cout << "Random" << endl;
        /* Fill the vector with a random permutation */
        randomPermutation(instance.getNbJob(), solution);
    }
    else if (s == "--simp")
    {
        simpRZsolution(instance.getNbJob(), solution, instance);
    }

    cout << "Solution: " ;
    for (i = 1; i <= instance.getNbJob(); ++i)
        cout << solution[i] << " " ;
    cout << endl;
    bool (*foo)(vector<int> sol, PfspInstance instance, long int curr_score) = &firstImprovement;
    string p = argv[3];
    if (p == "--tran")
    {
        for (int u = 0; u < 10; u++) {
            Transpose transpose = Transpose(solution, instance, foo);
            solution = transpose.generateTranspose(solution);
            if (not transpose.stop) break;
        }
    }
    else if (p == "--exch")
    {
        for (int u = 0; u < 10; u++) {
            Exchange exchange = Exchange(solution, instance, foo);
            solution = exchange.generateExchange(solution);
            if (not exchange.stop) break;
        }
    }
    else if (p == "--inse")
    {
        for (int u = 0; u < 10; u++) {
            Insert insert = Insert(solution, instance, foo);
            solution = insert.generateInsert(solution);
            if (not insert.stop) break;
        }
    }
    cout << "Solution: " ;
    for (i = 1; i <= instance.getNbJob(); ++i)
        cout << solution[i] << " " ;
    cout << endl;


    /* Compute the WCT of this solution */
    WeightedSumCompletionTimes = instance.computeWCT(solution);
    cout << "Total weighted completion time: " << WeightedSumCompletionTimes << endl;
    cout << "Total weighted tardiness: " << instance.computeWT(solution) << endl;

    return 0;
}
