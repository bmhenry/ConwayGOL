#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Life");

    menuBar = new QMenuBar(this);
    resetAction = menuBar->addAction("Reset");
    this->setMenuBar(menuBar);

    this->setFixedSize(400, 400 + menuBar->height());

    QWidget *w = new QWidget(this);
    w->setFixedSize(this->width(), this->height() - menuBar->height());
    this->setCentralWidget(w);

    QVBoxLayout *mainLayout = new QVBoxLayout(w);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    QWidget* spacer = new QWidget(this);
    spacer->resize(this->width(), menuBar->height());
    mainLayout->addWidget(spacer);

    canvas = new CanvasWidget(w);
    mainLayout->addWidget(canvas);

    connect(resetAction, SIGNAL(triggered(bool)), canvas, SLOT(resetCanvas()));

    canvas->repaint();
}

