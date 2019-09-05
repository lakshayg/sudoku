#include "minisat/core/Solver.h"
#include "sudoku.h"
#include <chrono>
#include <fstream>
#include <iostream>

using namespace Minisat;
using namespace std;
using namespace std::chrono;

void read_sudoku(std::string filename, Sudoku &s) {
  std::ifstream in(filename);
  for (int k = 0; k < 81; ++k) {
    int i(k / 9), j(k % 9);
    in >> s(i, j);
  }
  in.close();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "No input file provided" << endl;
    exit(-1);
  }

  Sudoku sudoku;
  read_sudoku(argv[1], sudoku);

  if (not sudoku.valid()) {
    cerr << "The provided sudoku is invalid" << endl;
    exit(-1);
  }

  Solver s;

  Var v[9][9][10]; // i, j, d
  Lit x[9][9][10];
  for (int k = 0; k < 81; ++k) {
    int i(k / 9), j(k % 9);
    for (int d = 1; d < 10; ++d) {
      v[i][j][d] = s.newVar();
      x[i][j][d] = mkLit(v[i][j][d]);
    }
  }

  auto t1 = high_resolution_clock::now();
  // add clauses to the solver
  // each cell must contain only one of the 9 digits
  for (int k = 0; k < 81; ++k) {
    int i(k / 9), j(k % 9);
    vec<Lit> c;
    for (int d = 1; d <= 9; ++d) {
      c.push(x[i][j][d]);
    }
    s.addClause(c);
  }

  // only one digit can be true. others must be false
  for (int k = 0; k < 81; ++k) {
    int i(k / 9), j(k % 9);
    for (int d = 1; d <= 9; ++d) {
      for (int dp = d + 1; dp <= 9; ++dp) {
        s.addClause(~x[i][j][d], ~x[i][j][dp]);
      }
    }
  }

  // each digit can appear only once in a row
  for (int d = 1; d <= 9; ++d) {
    for (int i = 0; i < 9; ++i) {
      // only one of x[i][:][d] can be true
      for (int j = 0; j < 9; ++j) {
        for (int jp = j + 1; jp < 9; ++jp) {
          s.addClause(~x[i][j][d], ~x[i][jp][d]);
        }
      }
    }
  }

  // each digit can appear only once in a col
  for (int d = 1; d <= 9; ++d) {
    for (int j = 0; j < 9; ++j) {
      // only one of x[:][j][d] can be true
      for (int i = 0; i < 9; ++i) {
        for (int ip = i + 1; ip < 9; ++ip) {
          s.addClause(~x[i][j][d], ~x[ip][j][d]);
        }
      }
    }
  }

  // each digit can appear only once in a 3x3 block
  for (int d = 1; d <= 9; ++d) {
    for (int g = 0; g < 9; ++g) {
      int r(g / 3), c(g % 3);
      for (int i = 3 * r; i < 3 * r + 3; ++i) {
        for (int j = 3 * c; j < 3 * c + 3; ++j) {
          for (int ip = 3 * r; ip < 3 * r + 3; ++ip) {
            for (int jp = 3 * c; jp < 3 * c + 3; ++jp) {
              if (i != ip or j != jp) {
                s.addClause(~x[i][j][d], ~x[ip][jp][d]);
              }
            }
          }
        }
      }
    }
  }

  // add clauses for numbers which are already filled
  for (int k = 0; k < 81; ++k) {
    int i(k / 9), j(k % 9), d(sudoku(i, j));
    if (d != 0) {
      s.addClause(x[i][j][d]);
    }
  }

  s.solve();

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1).count();

  if (s.okay()) {
    // update the sudoku
    for (int k = 0; k < 81; ++k) {
      int i(k / 9), j(k % 9);
      if (sudoku(i, j) == 0) {
        for (int d = 1; d <= 9; ++d)
          if (s.model[v[i][j][d]] == l_True)
            sudoku(i, j) = d;
      }
    }
    sudoku.print();
  }

  cout << "time: " << duration * 1e-3 << " ms\n";
  return 0;
}
