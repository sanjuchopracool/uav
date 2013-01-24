#-------------------------------------------------
#
# Project created by QtCreator 2012-12-25T03:11:08
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App

TEMPLATE = app
DESTDIR = bin
OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += main.cpp \
    Plotter.cpp \
    colorwidget.cpp \
    colorlabel.cpp \
    graphwidget.cpp \
    SerialApp.cpp

HEADERS  += \
    Plotter.h \
    colorwidget.h \
    colorlabel.h \
    graphwidget.h \
    SerialApp.h

 win32 {
     SOURCES +=  SerialPortWin.cpp
     HEADERS += SerialPortWin.h
 }
 unix {
     SOURCES +=  serialport.cpp
     HEADERS +=    serialport.h
 }
FORMS += \
    colorwidget.ui

OTHER_FILES += \
    colorChooser.css \
    candy.qss

RESOURCES += \
    myres.qrc
