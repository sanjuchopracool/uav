#include "SerialPlotter.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialPlotter w;
    QFile style(":/candy.qss");
    if(!style.open(QIODevice::ReadOnly))
        qDebug() << "Unable to open file";
    QString styleString = style.readAll();
    style.close();
//    w.plotter()->setCurveData(0,&dataVector1,QPen(Qt::red));
//    w.plotter()->setCurveData(1,&dataVector2,QPen(Qt::blue));
//    w.setStyleSheet(styleString);
    w.show();
    w.setWhatsThis("Serial port Plot is used to get data from serial and plot curves");
    return a.exec();
}
