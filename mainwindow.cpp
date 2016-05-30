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

    int x = 1200;
    int y = 800;
    this->setFixedSize(x, y + menuBar->height());

    QWidget *w = new QWidget(this);
    w->setFixedSize(x, y);
    this->setCentralWidget(w);

    QVBoxLayout *mainLayout = new QVBoxLayout(w);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    QWidget* spacer = new QWidget(this);
    spacer->resize(x, menuBar->height());
    mainLayout->addWidget(spacer);

    canvas = new CanvasWidget(x, y, w);
    mainLayout->addWidget(canvas);

    connect(resetAction, SIGNAL(triggered(bool)), canvas, SLOT(resetCanvas()));

    canvas->repaint();
}

