#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T17:39:32
#
#-------------------------------------------------

QT       += core gui
LIBS += -lWs2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sever
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread1.cpp \
    thread2.cpp \
    thread3.cpp \
    thread4.cpp

HEADERS  += mainwindow.h \
    thread1.h \
    Class.h \
    thread2.h \
    thread3.h \
    thread4.h

FORMS    += mainwindow.ui
