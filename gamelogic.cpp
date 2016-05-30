#include "gamelogic.h"

#include <QDebug>
#include <QTime>

GameLogic::GameLogic(int rows, int columns, int time, QObject* parent)
    : QObject(parent), rows(rows), columns(columns)
{
    // set avg percentage of the cells that should be 'live' when board is reset
    randomPercentage = 5;

    // create repeating timer for length of each game generation
    timer = new QTimer();
    timer->setInterval(time);
    timer->setSingleShot(false);

    // initialize pseudo-random generator
    qsrand(QTime::currentTime().msec());

    board = new Board(rows, columns);
    resetBoard();

    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));

    timer->start();
}

GameLogic::~GameLogic() {
    delete board;
    delete timer;
}

void GameLogic::resetBoard() {
    // resets the game board randomly

    int random;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            random = qrand() % 100; // get pseudo-random value from qrand

            if (random < randomPercentage)
                board->set(i, j, 1); // cell is live
            else
                board->set(i, j, 0); // cell is dead
        }
    }
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

            // implement game rules for life and death
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

    delete board;
    board = tempBoard;

    // tell CanvasWidget to repaint
    emit gameUpdate(board);
}

int GameLogic::getLiveNeighbors(int row, int column) {
    // gets the number of live neighbors a cell has

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
