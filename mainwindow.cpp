#include "mainwindow.h"

#include <QVBoxLayout>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *w = new QWidget(this);
    this->setCentralWidget(w);

    QVBoxLayout *mainLayout = new QVBoxLayout(w);

    helloLabel = new QLabel("Hello!", w);
    mainLayout->addWidget(helloLabel);
}
