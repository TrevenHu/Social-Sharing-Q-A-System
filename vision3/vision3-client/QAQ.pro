#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T11:01:16
#
#-------------------------------------------------

QT       += core gui
LIBS += -lWs2_32

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
    answerform.cpp \
    register.cpp \
    person.cpp

HEADERS  += mainwindow.h \
    login.h \
    Class.h \
    createques.h \
    listwidegt.h \
    answercontent.h \
    createans.h \
    focuslist.h \
    answerform.h \
    register.h \
    person.h

FORMS    += mainwindow.ui \
    login.ui \
    createques.ui \
    listwidegt.ui \
    answercontent.ui \
    createans.ui \
    focuslist.ui \
    answerform.ui \
    register.ui \
    person.ui

RESOURCES += \
    resource.qrc

OTHER_FILES +=
