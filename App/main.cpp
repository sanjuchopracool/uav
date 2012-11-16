#include "SerialApp.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialApp w;
    QFile style(":/candy.qss");
    if(!style.open(QIODevice::ReadOnly))
        qDebug() << "Unable to open file";
    QString styleString = style.readAll();
    w.setStyleSheet(styleString);
    w.show();
    
    return a.exec();
}
