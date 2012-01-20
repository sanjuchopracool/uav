#-------------------------------------------------
#
# Project created by QtCreator 2012-01-19T11:40:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = receiveport
CONFIG   += console
CONFIG   -= app_bundle
LIBS += -l qextserialport
TEMPLATE = app
DEFINES += _TTY_POSIX_
SOURCES += main.cpp \
    receiveport.cpp

HEADERS += \
    receiveport.h
