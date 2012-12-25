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
UI_DIR = ui
MOC_DIR = moc

SOURCES += main.cpp \
    Plotter.cpp \
    colorwidget.cpp \
    colorlabel.cpp \
    graphwidget.cpp \
    SerialApp.cpp \
    serialport.cpp

HEADERS  += \
    Plotter.h \
    colorwidget.h \
    colorlabel.h \
    graphwidget.h \
    SerialApp.h \
    serialport.h

FORMS += \
    colorwidget.ui

OTHER_FILES += \
    colorChooser.css \
    candy.qss

RESOURCES += \
    myres.qrc
