#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oglmouse1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    res/Point.cpp \
    res/CubicBezier.cpp \
    res/Poly.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    res/Point.hpp \
    res/CubicBezier.hpp \
    res/Poly.h

FORMS    += mainwindow.ui
