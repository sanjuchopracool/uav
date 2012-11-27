#-------------------------------------------------
#
# Project created by QtCreator 2012-11-16T21:58:22
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UARTPlotter
TEMPLATE = app
DESTDIR = bin
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc

SOURCES += main.cpp\
        SerialApp.cpp \
    serialport.cpp \
    Plotter.cpp \
    SerialPlotter.cpp \
    colorlabel.cpp \
    colorwidget.cpp

HEADERS  += SerialApp.h \
    serialport.h \
    Plotter.h \
    SerialPlotter.h \
    colorlabel.h \
    colorwidget.h

RESOURCES += \
    myres.qrc

OTHER_FILES += \
    candy.qss \
    images/zoom-out.png \
    images/zoom-in.png \
    colorChooser.css

FORMS += \
    colorwidget.ui
