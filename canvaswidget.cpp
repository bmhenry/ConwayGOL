#include "canvaswidget.h"

#include <QDebug>
#include <QPainter>
#include <QRect>
//#include <QMatrix>


CanvasWidget::CanvasWidget(QWidget* parent)
    : QOpenGLWidget(parent), board(NULL)
{
    this->setFixedSize(parent->size());

    sq_width = 5;

    logic = new GameLogic(this->height()/sq_width, this->width()/sq_width);
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
    Qt::GlobalColor color;
    painter.setPen(Qt::white);
    painter.setBackground(Qt::black);


    for (int row = 0; row < board->row_count; row++) {
        for (int col = 0; col < board->col_count; col++) {
            cell = board->get(row, col);
            if (cell == 1)
                color = Qt::black;
            else if (cell == 0)
                color = Qt::white;
            else
                qDebug() << cell;
            painter.fillRect(row*sq_width, col*sq_width, sq_width, sq_width, color);
        }
    }
}
