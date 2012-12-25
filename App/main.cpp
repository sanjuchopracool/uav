#include <QApplication>
#include "graphwidget.h"
#include "SerialApp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QVBoxLayout layout;
    GraphWidget graphWidget;
    SerialApp serialWidget;
    layout.addWidget(&serialWidget);
    layout.addWidget(&graphWidget);
    graphWidget.setVisible(false);

    QObject::connect(&serialWidget,SIGNAL(showPlotButtonSignal()),&graphWidget,SLOT(toggleVisibility()));
    QObject::connect(&graphWidget,SIGNAL(maximizeButtonSignal()),&serialWidget,SLOT(toogleVisibility()));
    QObject::connect(&serialWidget,SIGNAL(lineReceivedApp(QByteArray)),
                     &graphWidget,SLOT(lineReceiveSlot(QByteArray)));
    QObject::connect(&serialWidget,SIGNAL(closePortSignal()),&graphWidget,SLOT(stopButtonSlot()));

    w.setLayout(&layout);
    w.show();
    return a.exec();
}
