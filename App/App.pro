#-------------------------------------------------
#
# Project created by QtCreator 2012-11-16T21:58:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app


SOURCES += main.cpp\
        SerialApp.cpp \
    serialport.cpp \
    Plotter.cpp

HEADERS  += SerialApp.h \
    serialport.h \
    Plotter.h

RESOURCES += \
    myres.qrc

OTHER_FILES += \
    candy.qss \
    images/zoom-out.png \
    images/zoom-in.png
