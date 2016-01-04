#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T15:54:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = accounting_proj
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    category.cpp \
    statis_detail.cpp \
    file_client.c \
    utils.c \
    stype.c

HEADERS  += mainwindow.h \
    category.h \
    statis_detail.h \
    file_client.h \
    utils.h \
    stype.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
