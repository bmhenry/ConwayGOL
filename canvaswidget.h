#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QOpenGLWidget>

#include "gamelogic.h"


/*
 * CanvasWidget:
 *   Handles calls to GameLogic and drawing as a OpenGLWidget
 */
class CanvasWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(int width, int height ,QWidget* parent = 0);
    ~CanvasWidget();

    void drawGrid(int rows = 0, int columns = 0);

protected:
    virtual void paintEvent(QPaintEvent *);

public slots:
    void resetCanvas();
    void updateCanvas(Board*);

private:
    int sq_width;

    Board* board;
    GameLogic *logic;
};

#endif // CANVASWIDGET_H
