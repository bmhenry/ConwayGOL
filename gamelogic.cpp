#include "gamelogic.h"

#include <QDebug>
#include <QTime>

GameLogic::GameLogic(int rows, int columns, int time, QObject* parent)
    : QObject(parent), rows(rows), columns(columns)
{
    randomPercentage = 7;

    timer = new QTimer();
    timer->setInterval(time);
    timer->setSingleShot(false);

    qsrand(QTime::currentTime().msec());

    board = new Board(rows, columns);
    resetBoard();

    // TODO: method to initialize a map of the cells for which
    // start alive

    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));

    timer->start();
}

GameLogic::~GameLogic() {
    delete board;
    delete tempBoard;
    delete timer;
}

void GameLogic::resetBoard() {
    int random;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            random = qrand() % 100;

            if (random < randomPercentage)
                board->set(i, j, 1);
            else
                board->set(i, j, 0);
        }
    }
//    board->set(5, 5, 1);
//    board->set(5, 6, 1);
//    board->set(5, 7, 1);
//    board->set(3, 6, 1);

//    board->set(7, 5, 1);
//    board->set(7, 6, 1);
//    board->set(7, 7, 1);
//    board->set(9, 6, 1);
}

void GameLogic::timerEvent() {
    // update board for live/dead cells
    int ln;
    int cell;

    tempBoard = new Board(rows, columns);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            ln = getLiveNeighbors(r, c);
            cell = board->get(r, c);

            if (cell == 1) {
                if (ln < 2 or ln > 3)
                    tempBoard->set(r, c, 0);
                else
                    tempBoard->set(r, c, 1);
            }
            else if (cell == 0) {
                if (ln == 3)
                    tempBoard->set(r, c, 1);
            }
        }
    }

//    Board* transfer = board;
//    board = tempBoard;
//    tempBoard = transfer;
    delete board;
    board = tempBoard;

    emit gameUpdate(board);
}

int GameLogic::getLiveNeighbors(int row, int column) {
    int liveCounter = 0;

    // left side
    liveCounter += board->get(row - 1, column - 1);
    liveCounter += board->get(row, column - 1);
    liveCounter += board->get(row + 1, column - 1);
    // top and bottom
    liveCounter += board->get(row - 1, column);
    liveCounter += board->get(row + 1, column);
    // right side
    liveCounter += board->get(row - 1, column + 1);
    liveCounter += board->get(row, column + 1);
    liveCounter += board->get(row + 1, column + 1);

    return liveCounter;
}

void GameLogic::pause() {
    timer->stop();
}

void GameLogic::resume() {
    if (!timer->isActive())
        timer->start();
}
