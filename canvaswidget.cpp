#include "canvaswidget.h"

#include <QDebug>
#include <QPainter>
#include <QRect>
//#include <QMatrix>


CanvasWidget::CanvasWidget(int width, int height, QWidget* parent)
    : QOpenGLWidget(parent), board(NULL)
{
    this->setFixedSize(width, height);

    // set width of game squares and update time for game iterations
    sq_width = 5;
    int time = 1000;

    logic = new GameLogic(width/sq_width, height/sq_width, time);
    connect(logic, SIGNAL(gameUpdate(Board*)), this, SLOT(updateCanvas(Board*)));
}

CanvasWidget::~CanvasWidget() {
    delete logic;
    // board gets deleted by GameLogic
}

void CanvasWidget::resetCanvas() {
    // called by menu bar "Reset" to restart the board
    logic->pause();
    logic->resetBoard();
    logic->resume();
}

void CanvasWidget::updateCanvas(Board *b) {
    // slot that gets the new board from GameLogic
    board = b;

    repaint();
}

void CanvasWidget::paintEvent(QPaintEvent *) {
    // repaints the board

    if (board == NULL)
        return;

    QPainter painter(this);

    // fill board with white (faster than drawing a all the white squares individually)
    painter.fillRect(0, 0, this->width(), this->height(), Qt::white);


    // set 'live' black cells where necessary
    for (int row = 0; row < board->row_count; row++) {
        for (int col = 0; col < board->col_count; col++) {
            if (board->get(row, col) == 1)
                painter.fillRect(row*sq_width, col*sq_width, sq_width, sq_width, Qt::black);
        }
    }
}
