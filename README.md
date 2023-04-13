# Info-H-413 Heuristic Optimisation
## Implementation exercise 1
### Compile the code
To compile the project run

```bash
    make program
```

### Run the assignments
#### Ex 1.1
The first assignment is a set of 12 iterative improvement algorithms.
There are two possible pivoting rules:
- First-improvement
- Best-improvement

There are 3 possible neighbourhoods:
- transpose
- exchange
- insert

There are 2 possible starting solutions:
- random uniform permutation
- simplified RZ heuristic

Each algorithm has to run 5 times on the 20 instances of the PFSP, to run them all just run:

```bash
    ./ex1.1
```

The run time and resulting total weighted tardiness of each instance solution will be writen in csv files.
The files are named after the inputs of the main program (see independent run for more information).
Data in each file won't be ordered by default but a set of result files is already given in the directory "IterativeImprovementResults".

#### Ex 1.2
The second assignment is a set of 2 variable neighbourhood descent algorithms but the way the program is implemented allows 8 different algorithms to be run.
The 2 algorithms necessary for the assignment use 2 orderings or neighbourhoods:
- transpose, exchange, insert
- transpose, insert, exchange

Again each algorithm has to run 5 times on the 20 instances of the PFSP, to run them all just run:

```bash
    ./ex1.2
```

And again resulting data is registered in a file corresponding to each run.
Data in each file won't be ordered by default but a set of result files is already given in the directory "VNDResults"

### Independent run
The program can also be run independently for each algorithm. To do that run:

```bash
    ./pfspwt algorithmType pivotingRule neighbourhood startingSolution
```

The possible parameters are the following:

algorithmType: 
- --ii for iterative improvement
- --vnd for variable neighbourhood descent

pivotingRule:
- --first for first-improvement
- --best for best-improvement

The neighbourhood depend on the algorithmType:
- for --ii
  - --transpose
  - --insert
  - --exchange
- for --vnd
  - --tei for transpose -> exchange -> insert
  - --tie for transpose -> insert -> exchange

startingSolution:
- --rand for random uniform permutation
- --srz for simplified RZ heuristic

For example:
```bash
    ./pfspwt -ii --best --transpose --rand
```
Will run the iterative improvement algorithm with the best-improvement pivoting rule, the transpose neighbourhood and a random starting solution

And
```bash
    ./pfspwt --vnd --first --tei --srz
```
Will run the variable neighbourhood algorithm with the first-improvement pivoting rule, the order of neighbourhood will be
transpose -> exchange -> insert, and the starting solution will be the simplified RZ heuristic one.

Running any algorithm this way will run it 5 times on each of the 20 instances and give an unordered output data file in the main directory.