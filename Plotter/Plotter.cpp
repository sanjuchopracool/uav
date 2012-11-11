#include "Plotter.h"
#include<QtGui>
#include <cmath>

Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{
   // backgroundColor = QColor(100,93,90);
    textColor = Qt::blue;
    gridColor = QColor(100,93,90);
    antiAliasing = false;
    showGrid  = false;
    xAxisText = "X-Axis";
    yAxisText = "y-Axis";
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    rubberBandShown = false;
    zoomInButton = new QToolButton(this);
    zoomInButton->setToolTip("Zoom In (+)");
    zoomInButton->setIconSize(QSize(35,35));
    zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    zoomOutButton = new QToolButton(this);
    zoomOutButton->setToolTip("Zoom out (-)");
    zoomOutButton->setIconSize(QSize(35,35));
    zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

    showGridButton = new QToolButton(this);
    showGridButton->setCheckable(true);
    showGridButton->setToolTip("Show Grid");
    showGridButton->setIconSize(QSize(35,35));
    showGridButton->setIcon(QIcon(":/images/showgrid.png"));
    showGridButton->adjustSize();
    connect(showGridButton, SIGNAL(clicked()), this, SLOT(showGridSlot()));

    setPlotSettings(PlotSettings());


}

void Plotter::setPlotSettings(const PlotSettings& settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->setEnabled(false);
    zoomOutButton->setEnabled(false);
    refreshPixmap();
}

void Plotter::zoomOut()
{
    if(curZoom > 0)
    {
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refreshPixmap();
    }
}

void Plotter::showGridSlot()
{
    showGrid = !showGrid;
    if(showGrid)
        showGridButton->setToolTip("Hide Grid");
    else
        showGridButton->setToolTip("Show Grid");
    refreshPixmap();
}

void Plotter::zoomIn()
{
    if(curZoom < (zoomStack.count() -1))
    {
        ++curZoom;
        zoomInButton->setEnabled(curZoom <(zoomStack.count() -1));
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refreshPixmap();
    }
}
void Plotter::setCurveData(int id, QVector<QPointF> &data, QPen pen)
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
   // qDebug() << "Painitng ++++++++++++++++++++++";
    QStylePainter painter(this);
    painter.drawPixmap(0,0,pixmap);

    if(rubberBandShown)
    {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized().adjusted(0 , 0 , -1 , -1));
    }
    if(hasFocus())
    {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect,option);
    }
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    int x = width() - zoomInButton->width() -zoomInButton->width() - showGridButton->width() - 15 ;
    showGridButton->move(x, 5 );
    zoomInButton->move(x + 5 + showGridButton->width() , 5);
    zoomOutButton->move(x + 10 + zoomInButton->width() + showGridButton->width(), 5);
    refreshPixmap();
    zoomStack[0].adjust();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin,Margin,
               width() - 2 * Margin , height() - 2 * Margin);
    if(event->button() == Qt::LeftButton)
    {
        if(rect.contains(event->pos()))
        {
            rubberBandShown = true;
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);
        }
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
    if(rubberBandShown)
    {
        updateRubberBandRegion();
        rubberBandRect.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && rubberBandShown)
    {
        rubberBandShown = false ;
        updateRubberBandRegion();
        unsetCursor();

        QRect rect = rubberBandRect.normalized();
        if ( rect.width() < 4 && rect.height() < 4)
            return ;
        rect.translate(-Margin,-Margin);
        PlotSettings prevSetting = zoomStack[curZoom];

        PlotSettings settings;

        double dx = prevSetting.spanX() /(width() - 2 * Margin);
        double dy = prevSetting.spanY() /(height() - 2 * Margin);

        settings.minX = prevSetting.minX + dx * rect.left();
        settings.maxX = prevSetting.minX + dx * rect.right();
        settings.minY = prevSetting.maxY - dy * rect.bottom();
        settings.maxY = prevSetting.maxY - dy * rect.top();

        settings.adjust();

        zoomStack.resize(curZoom+1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
}

void Plotter::wheelEvent(QWheelEvent *event)
{
}


void Plotter::updateRubberBandRegion()
{
    QRect rect = rubberBandRect.normalized();
    update(rect.left(), rect.top(), rect.width(), 1);
    update(rect.left(), rect.top(), 1, rect.height());
    update(rect.left(), rect.bottom(), rect.width(), 1);
    update(rect.right(), rect.top(), 1, rect.height());

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
        painter.save();
        painter.translate( x - 10 ,rect.bottom() + 107);
        painter.rotate(-90);
        painter.drawText(0,0 , 100 ,20 ,Qt::AlignRight|Qt::AlignVCenter,QString::number(label));
        painter.restore();

        if(showGrid)
        {
            float miniStep = ((rect.width() -1.0)/(setting.numXTicks*10.0));
            painter.save();
            painter.setPen(gridColor);
            float offset;
            for( int j= 0 ; j < 10 && i <setting.numXTicks ; j++)
            {
                offset = miniStep*j;
                painter.drawLine(x + offset , rect.top() , x + offset , rect.bottom());
            }
            painter.restore();

        }
    }

    for(int i = 0 ; i <= setting.numYTicks ;i++ )
    {
        int y = rect.bottom() - ((i * (rect.height()-1))/setting.numYTicks);
        painter.drawLine(rect.left(), y ,rect.left() - 5 , y);
        double label = setting.minY + ((i*setting.spanY()) /setting.numYTicks);
        painter.drawText(rect.left() - Margin ,y - 10 ,

                         Margin-5 ,20 ,Qt::AlignRight|Qt::AlignVCenter,QString::number(label));
        if(showGrid)
        {
            float miniStep = ((rect.height() -1.0)/(setting.numYTicks*10.0));
            float offset;
            painter.save();
            painter.setPen(gridColor);
            for( int j= 0 ; j < 10 && i <setting.numYTicks ; j++)
            {
                offset = miniStep*j;
                painter.drawLine( rect.left() ,y - offset ,  rect.right() ,y - offset );
            }
            painter.restore();
        }
    }
    painter.save();
    painter.translate(rect.left() + rect.width()/2 , rect.bottom() + 30);
    painter.drawText(-100,0,200,20,Qt::AlignHCenter,xAxisText);
    painter.restore();

    painter.save();
    painter.translate(rect.left() - 40,rect.bottom() -rect.height()/2);
    painter.rotate(-90);
    painter.drawText(-100,0,200,20,Qt::AlignHCenter,yAxisText);
    painter.restore();

    painter.drawRect(rect.adjusted( 0 , 0 , -1 , -1));
}

void Plotter::drawCurves(QPainter& painter)
{
    QRect rect(Margin,Margin,
               width() - 2 * Margin , height() - 2 * Margin);
    if(!rect.isValid())
        return;
    PlotSettings setting = zoomStack[curZoom];

    /*
     *otherwise paint will be on every part
     */
    painter.setClipRect(rect.adjusted( 1 , 1 , - 1 , -1 ));

    QMapIterator<int , QVector<QPointF> > i(curveMap);
    while(i.hasNext())
    {
        i.next();
        int id = i.key();
        QVector <QPointF> data = i.value();
        int count = data.count();
       // qDebug() << "++++++++++++++++++++++++++++++++++++++++++++";
        QPolygonF polyline(count);
        for(int j = 0; j < count ;j++)
        {
            double dx = data[j].x() - setting.minX;
            double dy = data[j].y() - setting.minY;

            double x = rect.left() + (dx * (rect.width()-1))/setting.spanX();
            double y = rect.bottom() - (dy*(rect.height()-1))/setting.spanY();

            polyline[j] = QPointF(x,y);
          //  qDebug() << QPointF(x,y);
        }
        if(antiAliasing)
            painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(penMap.value(id));
        painter.drawPolyline(polyline);
    }
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
   // qDebug() <<std::floor(std::log10(grossStep));
    double step =std::pow(10.0,std::floor(std::log10(grossStep)));
    //qDebug() <<step;
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
