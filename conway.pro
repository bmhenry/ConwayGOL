#-------------------------------------------------
#
# Project created by QtCreator 2016-05-28T18:17:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conway
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    gamelogic.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    gamelogic.h \
    board.h

FORMS    +=

DISTFILES += \
    Rules.txt \
    .travis.yml
