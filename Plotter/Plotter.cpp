#include "Plotter.h"
#include <QToolButton>
#include <QPalette>
#include <QPainter>
#include <QStylePainter>
#include <QRect>
#include <cmath>
#include <QDebug>

Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{
   // backgroundColor = Qt::gray;
    textColor = Qt::white;
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    rubberBandShown = false;
    zoomInButton = new QToolButton(this);
    zoomInButton->setIconSize(QSize(40,40));
    zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIconSize(QSize(40,40));
    zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
    setPlotSettings(PlotSettings());


}

void Plotter::setPlotSettings(const PlotSettings& settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refreshPixmap();
}

void Plotter::setCurveDate(int id, QVector<QPointF> &data, QPen &pen)
{
    curveMap[id] = data;
    penMap[id] = pen;
    refreshPixmap();
}

void Plotter::clearCurve(int id)
{
    curveMap.remove(id);
    refreshPixmap();
}

QSize Plotter::minimumSizeHint() const
{
    return QSize(Margin*6,Margin*4);
}

QSize Plotter::sizeHint() const
{
    return QSize(Margin*12 ,Margin*8);
}

void Plotter::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,pixmap);
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    int x = width() - zoomInButton->width() -zoomInButton->width() - 10 ;
    zoomInButton->move(x , 5);
    zoomOutButton->move(x + 5 + zoomInButton->width() , 5);
    refreshPixmap();
    zoomStack[0].adjust();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
}

void Plotter::wheelEvent(QWheelEvent *event)
{
}

void Plotter::zoomIn()
{
    if(curZoom < (zoomStack.count() -1))
        ++curZoom;
    zoomInButton->setEnabled(curZoom <(zoomStack.count() -1));
    zoomOutButton->setEnabled(true);
    zoomOutButton->show();
    refreshPixmap();
}

void Plotter::zoomOut()
{
    if(curZoom > 0)
        curZoom--;
    zoomOutButton->setEnabled(curZoom > 0);
    zoomInButton->setEnabled(true);
    zoomInButton->show();
    refreshPixmap();
}

void Plotter::updateRubberBandRegion()
{
}

void Plotter::refreshPixmap()
{
    pixmap = QPixmap(size());
    pixmap.fill(backgroundColor);

    QPainter painter(&pixmap);
    drawGridAndText(painter);
    drawCurves(painter);
    update();

}

void Plotter::drawGridAndText(QPainter& painter)
{
    QRect rect(Margin,Margin,
               width() - 2 * Margin , height() - 2 * Margin);
    if(!rect.isValid())
        return;
    PlotSettings setting = zoomStack[curZoom];
    painter.setPen(textColor);
    for(int i = 0 ; i <= setting.numXTicks ;i++ )
    {
        int x = rect.left() + ((i * (rect.width()-1))/setting.numXTicks);
        painter.drawLine(x,rect.bottom(),x , rect.bottom() + 5);
        double label = setting.minX + ((i*setting.spanX()) /setting.numXTicks);
        painter.drawText(x-50,rect.bottom()+ 5 , 100 ,20 ,Qt::AlignHCenter|Qt::AlignTop,QString::number(label));
    }

    for(int i = 0 ; i <= setting.numYTicks ;i++ )
    {
        int y = rect.bottom() - ((i * (rect.height()-1))/setting.numYTicks);
        painter.drawLine(rect.left(), y ,rect.left() - 5 , y);
        double label = setting.minY + ((i*setting.spanY()) /setting.numYTicks);
        painter.drawText(rect.left() - Margin ,y - 10 , Margin-5 ,20 ,Qt::AlignRight|Qt::AlignVCenter,QString::number(label));
    }

    painter.drawRect(rect.adjusted( 0 , 0 , -1 , -1));
}

void Plotter::drawCurves(QPainter& painter)
{
}


PlotSettings::PlotSettings()
{
    minX =minY = 0.0;
    maxX = maxY = 10.0;
    numXTicks = numYTicks = 5;
}

void PlotSettings::scroll(int dx, int dy)
{
   double stepX = spanX();
   minX += stepX * dx;
   maxX += stepX * dx;

   double stepY = spanY();
   minY += stepY * dy;
   maxY += stepY * dy;

}

void PlotSettings::adjust()
{
    adjustAxis(minX,maxX,numXTicks);
    adjustAxis(minY,maxY,numYTicks);
}


void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;
    double grossStep = (max-min) / MinTicks;

    double step =std::pow(10.0,std::floor(std::log10(grossStep)));
    if (5 * step < grossStep) {
    step *= 5;
    } else if (2 * step < grossStep) {
    step *= 2;
    }
    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if (numTicks < MinTicks)
    numTicks = MinTicks;
    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;


}
