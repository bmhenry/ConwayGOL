#ifndef BOARD_H
#define BOARD_H

//class Board;

//class BoardHelper
//{
//private:
//    Board* parent;
//    int first;

//public:
//    BoardHelper(Board* parent, int first);
//    int &operator[](int second);
//};

class Board
{
public:
    Board(int rows, int columns);
    ~Board();

    int **cells;

    const int row_count;
    const int col_count;

//    BoardHelper operator[](int first);
    int get(int first, int second);
    void set(int first, int second, int value);
};

#endif // BOARD_H
