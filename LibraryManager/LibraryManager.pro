#-------------------------------------------------
#
# Project created by QtCreator 2017-08-05T12:08:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adoconn.cpp \
    login.cpp \
    student.cpp \
    manager.cpp \
    borrowbookinfo.cpp \
    borrowbook.cpp \
    returnbook.cpp \
    bookinfo.cpp

HEADERS  += mainwindow.h \
    adoconn.h \
    login.h \
    student.h \
    manager.h \
    borrowbookinfo.h \
    borrowbook.h \
    returnbook.h \
    bookinfo.h

FORMS    += mainwindow.ui \
    login.ui \
    student.ui \
    manager.ui \
    borrowbook.ui \
    returnbook.ui
