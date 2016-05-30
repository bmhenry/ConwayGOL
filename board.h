#ifndef BOARD_H
#define BOARD_H


/*
 * Board:
 *   Gameboard only, with no internal game logic
 */
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
