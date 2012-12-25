#include "Plotter.h"
#include <QStylePainter>
#include <QDebug>
#include <QFileDialog>

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

    maximizeButton = new QToolButton(this);
    maximizeButton->setCheckable(true);
    maximizeButton->setIcon(QIcon(":images/maximize.png"));
    maximizeButton->setToolTip("Maximize");
    maximizeButton->setIconSize(QSize(35,35));
    maximizeButton->adjustSize();

    curvePenButton = new QToolButton(this);
    curvePenButton->setIcon(QIcon(":images/style.png"));
    curvePenButton->setToolTip("Change color Settings");
    curvePenButton->setIconSize(QSize(35,35));
    curvePenButton->adjustSize();

    savePictureButton = new QToolButton(this);
    savePictureButton->setIcon(QIcon(":images/image-x-generic.png"));
    savePictureButton->setToolTip("Save as Image");
    savePictureButton->setIconSize(QSize(35,35));
    savePictureButton->adjustSize();

    antiAliasing = true;
    connect(maximizeButton,SIGNAL(clicked()),this,SIGNAL(maximizeButtonSignal()));
    connect(maximizeButton,SIGNAL(clicked()),this,SLOT(maximizeButtonSlot()));
    connect(curvePenButton,SIGNAL(clicked()),this,SLOT(changePlotSettingSlot()));
    connect(savePictureButton,SIGNAL(clicked()),this,SLOT(saveAsImage()));

    this->loadSettings();
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
    maximizeButton->move(this->rect().right() -45, 5);
    curvePenButton->move(this->rect().right() -95 , 5);
    savePictureButton->move(this->rect().right() -145 , 5);
}

QRect Plotter::printRect()
{
    return QRect(Margin,Margin,this->width() - 2*Margin,this->height()- 2*Margin);
}

void Plotter::setCurveData(int id, QList<double> *dataList)
{
    this->curveDataMap[id] = dataList;
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
//    qDebug() << "maxY is " << maxY;
//    qDebug() << "minY is " << minY;
    painter.setPen(QPen(textColor));
    painter.drawRect(this->printRect().adjusted(0,0,-1,-1));
    QRect rect = this->printRect();
    double width = rect.width() - 1;
    double stepX = 0;
    double bottom = rect.bottom();
    double label = 0;
    painter.save();
    painter.translate(Margin,bottom);
    for(int i = 0 ; i <= numXTicks ;i++)
    {
        label = (i*(noOfPoints + 1))/ numXTicks;
        stepX =  (width * i) / numXTicks;
        painter.drawLine(stepX ,0,stepX ,5);
        painter.drawText(QRect(stepX - 50,5,100,20),Qt::AlignCenter,QString::number(label));
    }
    painter.restore();

    double height = rect.height() - 1;
    double stepY = 0;
    double left = rect.left();
    painter.save();
    painter.translate(left,rect.bottom());
    for(int i = 0 ; i <= numYTicks ; i++)
    {
        label = minY + (i * (maxY - minY))/numYTicks;
        stepY = - (height * i) / numYTicks;
        painter.drawLine(0 , stepY ,0 - 5, stepY);
        painter.drawText(QRect(-105,stepY-10,100,20),Qt::AlignRight|Qt::AlignVCenter,QString::number(label));
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
    painter.setClipRegion(rect);
    painter.translate(Margin + 1,rect.bottom()-1);
    for(int i=0; i < noOfCurves ; i++)
    {
        QPolygonF polyline;
        QList<double>* dataPtr = curveDataMap[i] ;
        for(int j = 0 ; j <= noOfPoints ; j++)
        {
            x = (width * j)/noOfPoints;
            y = (height * (dataPtr->value(j) -minY))/yCount;
            polyline << QPoint(x,-y);
            //qDebug() << y;
        }
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


void Plotter::maximizeButtonSlot()
{
    if(!maximizeButton->isChecked())
    {
        maximizeButton->setToolTip("Maximize");
        maximizeButton->setIcon(QIcon(":images/maximize.png"));
    }
    else
    {
        maximizeButton->setToolTip("Minimize");
        maximizeButton->setIcon(QIcon(":images/minimize.png"));
    }
}

void Plotter::changePlotSettingSlot()
{
    QVector<QColor> vect(12);
    for(int i=0; i <12 ;i++)
        vect[i] = colorMap.value(i);
    ColorWidget cWidget;
    cWidget.move(this->rect().center().x() -200 , this->rect().center().y() -100);
    cWidget.getColor(backgroundColor,textColor,&vect);
    connect(&cWidget,SIGNAL(setColor(QColor,QColor,QVector<QColor>)),
            this,SLOT(applyColorSetting(QColor,QColor,QVector<QColor>)));
    cWidget.exec();

}

void Plotter::applyColorSetting(QColor back, QColor text, QVector<QColor> vect)
{
    this->colorMap.clear();
    this->setBackgroundColor(back);
    this->setTextColor(text);
    for(int i=0 ; i <12 ;i++)
        this->colorMap[i] = vect.at(i);
    this->saveSettings();
}

void Plotter::saveSettings()
{
    QFile xmlFile("setting.xml");
    if(!xmlFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug() << "unable to open";
        return;
    }

    QDomDocument document;
    QDomElement d =document.createElement("document");
    d.setAttribute("name" , "ColorSetting");
    QDomElement color[14];
    color[0] = document.createElement("backgroundcolor");
    color[0].setAttribute("value",backgroundColor.name());
    color[1] = document.createElement("textcolor");
    color[1].setAttribute("value",textColor.name());
    document.appendChild(d);
    d.appendChild(color[0]);
    d.appendChild(color[1]);
    for(int i=2;i<14;i++)
    {
        color[i] = document.createElement("color"+QString::number(i-2));
        color[i].setAttribute("value",colorMap.value(i-2).name());
        d.appendChild(color[i]);
    }

    QTextStream xmlStream(&xmlFile);
    xmlStream <<document.toString();
    xmlFile.close();
}

void Plotter::loadSettings()
{
    QDomDocument document;
    QFile file( "setting.xml" );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        for(int i=0;i <12 ;i++)
            colorMap[i] = QColor(qrand()%255,qrand()%255,qrand()%255);
        this->saveSettings();
        return ;
    }
    if( !document.setContent( &file ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        file.close();
        return;
    }
    file.close();
    QDomElement documentElement= document.documentElement();
    QDomNode node = documentElement.firstChild();
    QDomElement element = node.toElement();
    this->setBackgroundColor(QColor(element.attribute("value",QString())));
    node =node.nextSibling();
    element = node.toElement();
    this->setTextColor(QColor(element.attribute("value",QString())));
    node =node.nextSibling();
    int i=0;
    while(node.isElement())
    {
        element = node.toElement();
        colorMap[i]=QColor(element.attribute("value",QString()));
        node =node.nextSibling();
        i++;
    }
}

void Plotter::saveAsImage()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as Image",QDir::homePath(),"Image Files (*.png) ;");
    if(fileName.isEmpty())
        return;
    this->pixmap.save(fileName);
}
