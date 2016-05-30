#include "canvaswidget.h"

#include <QDebug>
#include <QPainter>
#include <QRect>
//#include <QMatrix>


CanvasWidget::CanvasWidget(int width, int height, QWidget* parent)
    : QOpenGLWidget(parent), board(NULL)
{
    this->setFixedSize(width, height);

    sq_width = 5;
    int time = 500;

    logic = new GameLogic(width/sq_width, height/sq_width, time);
    connect(logic, SIGNAL(gameUpdate(Board*)), this, SLOT(updateCanvas(Board*)));
}

CanvasWidget::~CanvasWidget() {
    delete logic;

    // board gets deleted by GameLogic
    //if (board != NULL)
    //    delete board;
}

void CanvasWidget::resetCanvas() {
    logic->pause();
    logic->resetBoard();
    logic->resume();
}

void CanvasWidget::updateCanvas(Board *b) {
    board = b;

    repaint();
}

void CanvasWidget::paintEvent(QPaintEvent *) {
    if (board == NULL)
        return;

    QPainter painter(this);
    int cell;

    painter.fillRect(0, 0, this->width(), this->height(), Qt::white);


    for (int row = 0; row < board->row_count; row++) {
        for (int col = 0; col < board->col_count; col++) {
            cell = board->get(row, col);
            if (cell == 1)
                painter.fillRect(row*sq_width, col*sq_width, sq_width, sq_width, Qt::black);
            else if (cell != 0)
                qDebug() << "Cell not 1 or 0: (" << row << "," << col << ") = " << cell;
        }
    }
}
