#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "pfspinstance.h"


using namespace std;

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



PfspInstance::PfspInstance()
{
}

PfspInstance::~PfspInstance()
{
}

int PfspInstance::getNbJob()
{
  return nbJob;
}



int PfspInstance::getNbMac()
{
  return nbMac;
}


/* Allow the memory for the processing times matrix : */
void PfspInstance::allowMatrixMemory(int nbJ, int nbM)
{
  processingTimesMatrix.resize(nbJ+1);          // 1st dimension

  for (int cpt = 0; cpt < nbJ+1; ++cpt)
    processingTimesMatrix[cpt].resize(nbM+1); // 2nd dimension

	dueDates.resize(nbJ+1);
	priority.resize(nbJ+1);
}


long int PfspInstance::getTime(int job, int machine)
{
  if (job == 0)
    return 0;
  else
  {
    if ((job < 1) || (job > nbJob) || (machine < 1) || (machine > nbMac))
      cout    << "ERROR. file:pfspInstance.cpp, method:getTime. Out of bound. job=" << job
          << ", machine=" << machine << std::endl;

    return processingTimesMatrix[job][machine];
  }
}


/* Read the instance from file : */
bool PfspInstance::readDataFromFile(char * fileName)
{
	bool everythingOK = true;
	int j, m; // iterators
	long int readValue;
	string str;
	ifstream fileIn;
	char * aux2;
	char fileNameOK[100] = "";

	aux2 = (strrchr(fileName, '/'));

	if (aux2 == NULL)
		aux2 = fileName;
	else
		aux2 += 1;

	strcat(fileNameOK, aux2);

	/*cout << "name : " << fileNameOK << endl;
	cout << "file : " << fileName << endl;*/

	fileIn.open(fileName);

	if ( fileIn.is_open() ) {
        /*cout << "File " << fileName << " is now open, start to read..." << std::endl;*/

		fileIn >> nbJob;
        /*cout << "Number of jobs : " << nbJob << std::endl;*/
		fileIn >> nbMac;
        /*cout << "Number of machines : " << nbMac << std::endl;
        cout << "Allow memory for the matrix..." << std::endl;*/
		allowMatrixMemory(nbJob, nbMac);
        /*cout << "Memory allowed." << std::endl;
        cout << "Start to read matrix..." << std::endl;*/

		for (j = 1; j <= nbJob; ++j)
		{
			for (m = 1; m <= nbMac; ++m)
			{
				fileIn >> readValue; // The number of each machine, not important !
				fileIn >> readValue; // Process Time

				processingTimesMatrix[j][m] = readValue;
			}
		}
        fileIn >> str; // this is not read

		for (j = 1; j <= nbJob; ++j)
		{
			fileIn >> readValue; // -1
			fileIn >> readValue;
			dueDates[j] = readValue;
			fileIn >> readValue; // -1
			fileIn >> readValue;
            priority[j] = readValue;
		}

        /*cout << "All is read from file." << std::endl;*/
		fileIn.close();
	}
	else
	{
		cout    << "ERROR. file:pfspInstance.cpp, method:readDataFromFile, "
				<< "error while opening file " << fileName << std::endl;

		everythingOK = false;
	}

	return everythingOK;
}

/* Compute the weighted sum of completion time of a given solution */
long int PfspInstance::computeWCT(vector< int > & sol)
{
	int j, m;
	int jobNumber;
	long int wct;

	/* We need end times on previous machine : */
	vector< long int > previousMachineEndTime ( nbJob + 1 );
	/* And the end time of the previous job, on the same machine : */
	long int previousJobEndTime;

	/* 1st machine : */
	previousMachineEndTime[0] = 0;
	for ( j = 1; j <= nbJob; ++j )
	{
		jobNumber = sol[j];
		previousMachineEndTime[j] = previousMachineEndTime[j-1] + processingTimesMatrix[jobNumber][1];
	}

	/* others machines : */
	for ( m = 2; m <= nbMac; ++m )
	{
		previousMachineEndTime[1] +=
				processingTimesMatrix[sol[1]][m];
		previousJobEndTime = previousMachineEndTime[1];


		for ( j = 2; j <= nbJob; ++j )
		{
			jobNumber = sol[j];

			if ( previousMachineEndTime[j] > previousJobEndTime )
			{
				previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[jobNumber][m];
				previousJobEndTime = previousMachineEndTime[j];
			}
			else
			{
				previousJobEndTime += processingTimesMatrix[jobNumber][m];
				previousMachineEndTime[j] = previousJobEndTime;
			}
		}
	}

	wct = 0;
	for ( j = 1; j<= nbJob; ++j )
	    wct += previousMachineEndTime[j] * priority[sol[j]];

	return wct;
}

long int PfspInstance::computeWT(vector<int> &sol) {
    // Initialise the matrix to compute th weighted tardiness
    vector < vector < long int > > computingMatrix(nbJob+1);
    for (int j=1; j <= nbJob; j++) {
        computingMatrix[j] = vector<long int>(nbMac+1);
        if (j==1) { // First column
            for (int m=1; m <= nbMac; m++) {
                if (m==1) computingMatrix[j][m] = this->getTime(sol[j],m);
                else computingMatrix[j][m] = computingMatrix[j][m-1] + this->getTime(sol[j],m);
            }
        }
        else { // Other columns
            for (int m=1; m <= nbMac; m++) {
                if(m==1) computingMatrix[j][m] = computingMatrix[j-1][m] + this->getTime(sol[j],m);
                else computingMatrix[j][m] = max(computingMatrix[j-1][m], computingMatrix[j][m-1]) + this->getTime(sol[j],m);
            }
        }
    }
    // Finally compute the total tardiness
    long int totalTardiness = 0;
    for (int j=1; j <= nbJob; j++) totalTardiness += max(computingMatrix[j][nbMac] - this->getDueDate(sol[j]), (long) 0)*this->getPriority(sol[j]);
    return totalTardiness;
}

long int PfspInstance::getPriority(int job) {
    return priority[job];
}

long PfspInstance::getDueDate(int job) {
    return dueDates[job];
}

long PfspInstance::getTotalJobTime() {
    long res = 0;
    for (int m = 1; m <= nbMac; m++) {
        for (int n = 1; n <= nbJob; n++) {
            res += processingTimesMatrix[n][m];
        }
    }
    return res;
}