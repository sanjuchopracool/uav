#include <QApplication>
#include "Plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plotter w;
    QVector<double> dataVector1(100) ,dataVector2(100);
    for(int i = 0 ; i < 100 ; i++)
    {
        dataVector1[i] = qrand() % 100 ;
        dataVector2[i] = qrand() % 100 ;
    }
    w.setCurveData(0,&dataVector1,QPen(Qt::red));
    w.setCurveData(1,&dataVector2,QPen(Qt::blue));
    w.show();
    
    return a.exec();
}
