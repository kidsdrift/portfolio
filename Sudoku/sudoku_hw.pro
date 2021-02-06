#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T17:58:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku_hw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sudoku.cpp \
    timer.cpp \
    solver.cpp

HEADERS  += mainwindow.h \
    sudoku.h \
    timer.h \
    solver.h

FORMS    += mainwindow.ui
