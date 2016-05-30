#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMenuBar>
#include <QAction>

#include "canvaswidget.h"
#include "board.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();

private:
    CanvasWidget* canvas;
    QMenuBar* menuBar;

    QAction* resetAction;
};

#endif // MAINWINDOW_H
