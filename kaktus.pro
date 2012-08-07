#-------------------------------------------------
#
# Project created by QtCreator 2012-07-17T16:49:52
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/kaktus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    browser.cpp \
    commandbar.cpp \
    cookiejar.cpp \
    storagemanager.cpp

HEADERS  += mainwindow.h \
    browser.h \
    commandbar.h \
    cookiejar.h \
    storagemanager.hpp

OTHER_FILES +=
