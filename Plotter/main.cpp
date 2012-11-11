#include <QApplication>
#include "Plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plotter w;
    QVector<QPointF> data(100) , data2(100);
    for(int i=0 ;i < 100 ;i++)
    {
        data[i] = QPointF(i, uint(qrand()) % 100);
        data2[i] = QPointF(i, uint(qrand()) % 100);
    }
    PlotSettings setting;
    setting.maxX = 100;
    setting.maxY = 100 ;
    w.setPlotSettings(setting);
   // w.setCurveData(1,data,QPen(Qt::red));
    w.setCurveData(2,data2,QPen(Qt::green));
    w.show();

    return a.exec();
}
