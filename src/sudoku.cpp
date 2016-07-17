#include "sudoku.h"
#include <cstdio>

Sudoku::Sudoku()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s[i][j] = 0;
        }
    }
}

Sudoku::Sudoku(const Sudoku& s) {}

Sudoku::Sudoku(Sudoku&& s) {}

int Sudoku::operator()(int row, int col) const { return s[row][col]; }

int& Sudoku::operator()(int row, int col) { return s[row][col]; }

bool Sudoku::valid() { return true; }

bool Sudoku::solved()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (s[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku::print()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf(" %d ", s[i][j]);
        }
        putchar('\n');
    }
}
