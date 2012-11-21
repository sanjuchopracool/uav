#include "Plotter.h"
#include <QStylePainter>
#include <QDebug>

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
    backgroundColor = Qt::black;
    textColor = Qt::blue;
    noOfCurves = 0;
    noOfPoints = 99;
    minY = 0;
    maxY = 100;
    this->numXTicks = 10;
    this->numYTicks = 10;
    antiAliasing = false;
}

void Plotter::refreshImage()
{
    this->pixmap = QPixmap(this->size());
    pixmap.fill(this->backgroundColor);
    QPainter painter(&pixmap);
    this->drawText(painter);
    this->drawCurves(painter);
    this->update();
}

void Plotter::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.drawPixmap(0 , 0 ,this->pixmap);
    this->refreshImage();
}

void Plotter::resizeEvent(QResizeEvent *)
{
}

QRect Plotter::printRect()
{
    return QRect(Margin,Margin,this->width() - 2*Margin,this->height()- 2*Margin);
}

void Plotter::setCurveData(int id, QVector<double> *dataVector, QPen curvePen)
{
    this->colorMap[id] = curvePen;
    this->curveDataMap[id] = dataVector;
    this->refreshImage();
}

void Plotter::setSetting(int no_Curves, int no_Points, int MinY, int MaxY)
{
    this->noOfCurves = no_Curves;
    this->noOfPoints = no_Points-1;
    this->minY = MinY;
    this->maxY = MaxY;
}

void Plotter::drawText(QPainter &painter)
{
    painter.setPen(QPen(textColor));
    painter.drawRect(this->printRect().adjusted(0,0,-1,-1));
    QRect rect = this->printRect();
    double width = rect.width() - 1;
    double stepX = 0;
    double bottom = rect.bottom();
    painter.save();
    painter.translate(Margin,bottom);
    for(int i = 0 ; i <= numXTicks ;i++)
    {
        stepX =  (width * i) / numXTicks;
        painter.drawLine(stepX ,0,stepX ,5);
    }
    painter.restore();

    double height = rect.height() - 1;
    double stepY = 0;
    double left = rect.left();
    painter.save();
    painter.translate(left,rect.bottom());
    for(int i = 0 ; i <= numYTicks ; i++)
    {
        stepY = - (height * i) / numYTicks;
        painter.drawLine(0 , stepY ,0 - 5, stepY);
    }
    painter.restore();

}

void Plotter::drawCurves(QPainter& painter)
{
    noOfCurves = curveDataMap.count();
    QRect rect = this->printRect();
    double x=0,y=0;
    double width = rect.width() - 1;
    double height = rect.height() - 1;
    double yCount = maxY - minY;
    if(antiAliasing)
        painter.setRenderHints(QPainter::Antialiasing);
    painter.translate(Margin + 1,rect.bottom()-1);
    for(int i=0; i < noOfCurves ; i++)
    {
        QPolygonF polyline;
        QVector<double>* dataPtr = curveDataMap[i] ;
        for(int j = 0 ; j <= noOfPoints ; j++)
        {
            x = (width * j)/noOfPoints;
            y = (height * dataPtr->value(j))/yCount;
            polyline << QPoint(x,-y);
            //qDebug() << y;
        }
        qDebug() << x <<rect.right();
        painter.setPen(colorMap.value(i));
        painter.drawPolyline(polyline);

    }
}

void Plotter::adjustTicks()
{
    if(!(noOfPoints % numXTicks))
        numXTicks +=1;
    if(!((maxY - minY) % numYTicks))
        numYTicks += 1;
}

Plotter::~Plotter()
{
    
}
