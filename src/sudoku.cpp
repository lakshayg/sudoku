#include "sudoku.h"
#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

Sudoku::Sudoku()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s[i][j] = 0;
        }
    }
}

Sudoku::Sudoku(const Sudoku& p)
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s[i][j] = p(i, j);
        }
    }
}

Sudoku::Sudoku(Sudoku&& s) {}

int Sudoku::operator()(int row, int col) const { return s[row][col]; }

int& Sudoku::operator()(int row, int col) { return s[row][col]; }

bool Sudoku::valid()
{
    // checks if the cells contain a valid entry
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (s[i][j] < 0 or s[i][j] > 9) {
                return false;
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (not row_valid(i)) return false;
        if (not col_valid(i)) return false;
        if (not box_valid(i)) return false;
    }
    return true;
}

bool Sudoku::solved()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (s[i][j] == 0) {
                return false;
            }
        }
    }
    return valid();
}

void Sudoku::print()
{
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) printf("+---------+---------+---------+\n");
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0) printf("|");
            printf(" %d ", s[i][j]);
        }
        printf("|\n");
    }
    printf("+---------+---------+---------+\n");
}

bool Sudoku::row_valid(int idx)
{
    vector<int> count(10, 0);
    for (int i = 0; i < 9; ++i) {
        int d = s[idx][i];
        if (d != 0) { // check only for non-empty cells
            if (count[d] > 0) {
                return false;
            }
            count[d]++;
        }
    }
    return true;
}

bool Sudoku::col_valid(int idx)
{
    vector<int> count(10, 0);
    for (int i = 0; i < 9; ++i) {
        int d = s[i][idx];
        if (d != 0) { // check only for non-empty cells
            if (count[d] > 0) {
                return false;
            }
            count[d]++;
        }
    }
    return true;
}

bool Sudoku::box_valid(int idx)
{
    vector<int> count(10, 0);
    for (int i = 3 * (idx / 3); i < 3 * (idx / 3) + 3; ++i) {
        for (int j = 3 * (idx % 3); j < 3 * (idx % 3) + 3; ++j) {
            int d = s[i][j];
            if (d != 0) { // check only for non-empty cells
                if (count[d] > 0) {
                    return false;
                }
                count[d]++;
            }
        }
    }
    return true;
}
