#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T11:01:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QAQ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    createques.cpp \
    listwidegt.cpp \
    answercontent.cpp \
    createans.cpp \
    focuslist.cpp \
    answerform.cpp

HEADERS  += mainwindow.h \
    login.h \
    Class.h \
    createques.h \
    listwidegt.h \
    answercontent.h \
    createans.h \
    focuslist.h \
    answerform.h

FORMS    += mainwindow.ui \
    login.ui \
    createques.ui \
    listwidegt.ui \
    answercontent.ui \
    createans.ui \
    focuslist.ui \
    answerform.ui

RESOURCES += \
    resource.qrc

OTHER_FILES +=
