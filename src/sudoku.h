#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
public:
    Sudoku();                ///< Default constructor
    Sudoku(const Sudoku& s); ///< Copy constructor
    Sudoku(Sudoku&& s);      ///< Move constructor

    int operator()(int row, int col) const; ///< Access value at (row,col)
    int& operator()(int row, int col);      ///< Modify value at (row,col)

    bool valid();  ///< Returns true if the sudoku is in a consistent state
    bool solved(); ///< Returns true if the sudoku is solved
    void print();  ///< Print the sudoku

private:
    int s[9][9]; ///< Sudoku data

    bool row_valid(int idx); ///< Checks if the given row is consistent
    bool col_valid(int idx); ///< Checks if the given column is consistent
    bool box_valid(int idx); ///< Checks if the given 3x3 box is consistent
};

#endif
