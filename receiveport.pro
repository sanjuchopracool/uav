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

TEMPLATE = app
DEFINES += _TTY_POSIX_
SOURCES += main.cpp \
    files/qextserialport.cpp \
    files/qextserialbase.cpp \
    files/posix_qextserialport.cpp \
    receiveport.cpp

HEADERS += \
    files/qextserialport.h \
    files/qextserialbase.h \
    files/posix_qextserialport.h \
    receiveport.h
