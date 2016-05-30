#include "board.h"
#include <QDebug>

Board::Board(int rows, int columns)
    : row_count(rows), col_count(columns)
{
    // create rows
    cells = new int*[row_count];

    if (row_count)
    {
        // create column members in each row
        for (int i = 0; i < row_count; ++i) {
            cells[i] = new int[col_count];
            for (int j = 0; j < col_count; ++j)
                cells[i][j] = 0;
        }
    }
}

Board::~Board() {
    // delete each row, then the whole matrix
    if (row_count and col_count)
        for (int i = 0; i < row_count; ++i)
            delete[] cells[i];

    delete[] cells;
}

int Board::get(int first, int second) {
    // provide wrap-around for the board edges
    if (first >= row_count)
        first -= row_count;
    else if (first < 0)
        first += row_count;

    if (second >= col_count)
        second -= col_count;
    else if (second < 0)
        second += col_count;

    return cells[first][second];
}

void Board::set(int first, int second, int value) {
    // provide wrap-around for the board edges
    if (first > row_count)
        first -= row_count;
    else if (first < 0)
        first += row_count;

    if (second > col_count)
        second -= col_count;
    else if (second < 0)
        second += col_count;

    cells[first][second] = value;
}
