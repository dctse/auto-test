#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T15:25:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWindowApp
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp

HEADERS  += mainview.h

FORMS    += mainview.ui

QMAKE_CXXFLAGS += -std=c++11
