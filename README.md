# Sudoku solver
This project solves sudoku puzzles by formulating it as a [boolean satisfiability problem](https://en.wikipedia.org/wiki/Boolean_satisfiability_problem).
It uses [minisat](http://minisat.se/) to solve the SAT problem.

## Obtaining the sovler
```
git  clone https://github.com/lakshayg/sudoku
cd sudoku
git submodule init
git submodule update
```

## Building the sovler
Go to the project root directory and follow these steps to compile the solver (make sure you are using g++ and not clang)
```
mkdir build
cd build
cmake .. && make
```
This will generate an executable named `main` in the build directory. This is the solver.

## Using the solver
The solver takes a text file as the input. Some sample puzzles are provided in the demo folder. To solve a puzzle, create a text file containing the puzzle. Use `0` for blank cells. An example is shown below:
```
0  0  0  0  0  0  1  9  0
0  0  1  7  0  0  0  0  8
0  4  9  2  0  0  0  6  0
0  0  0  3  0  0  0  0  0
8  0  0  0  0  7  3  0  0
0  0  0  6  0  5  0  0  2
0  8  0  0  0  9  0  0  0
0  0  4  0  0  0  5  0  0
5  0  0  0  0  0  2  1  4
```
Now go into the build directory and use the following command
```
./main <path-to-puzzle-file>
```
This should print out the solved puzzle on the terminal screen.
```

  2    7    8    5    6    4   |1|  |9|   3  

  6    5   |1|  |7|   9    3    4    2   |8| 

  3   |4|  |9|  |2|   8    1    7   |6|   5  

  4    1    5   |3|   2    8    9    7    6  

 |8|   2    6    9    4   |7|  |3|   5    1  

  9    3    7   |6|   1   |5|   8    4   |2| 

  1   |8|   2    4    5   |9|   6    3    7  

  7    6   |4|   1    3    2   |5|   8    9  

 |5|   9    3    8    7    6   |2|  |1|  |4| 


Solved the puzzle in 3.836 ms :)
```
