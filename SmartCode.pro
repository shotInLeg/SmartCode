#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T23:18:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCode
TEMPLATE = app


SOURCES += main.cpp\
        smartcode.cpp \
    Highlighter/highlighter.cpp \
    ACC/acp.cpp

HEADERS  += smartcode.h \
    Highlighter/highlighter.h \
    ACC/acp.h

FORMS    += smartcode.ui
