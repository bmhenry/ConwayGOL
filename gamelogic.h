#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QTimer>
#include <QObject>

#include "board.h"


class GameLogic : public QObject
{
    Q_OBJECT

public:
    const int rows;
    const int columns;

    GameLogic(int rows, int columns, int time = 1000, QObject* parent = 0);
    ~GameLogic();
    void resetBoard();

    void pause();
    void resume();

private:
    QTimer *timer;
    Board* board;
    Board* tempBoard;

    int randomPercentage;

    int getLiveNeighbors(int row, int column);

private slots:
    void timerEvent();

signals:
    void gameUpdate(Board*);
};

#endif // GAMELOGIC_H
