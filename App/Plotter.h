#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMap>
#include <QVector>
#include <QColor>
#include <QToolButton>
#include "colorwidget.h"
#include <QDomDocument>
#include <QDomElement>
#include <QFile>

class Plotter : public QWidget
{
    Q_OBJECT
    
public:
    Plotter(QWidget *parent = 0);
    void refreshImage();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    QRect printRect();
    void setCurveData(int id ,QList<double>* dataList);
    void setSetting(int no_Curves , int no_Points , int MinY , int MaxY);
    void drawText(QPainter& painter);
    void drawCurves(QPainter& painter);
    void drawGrid(QPainter& painter);
    void adjustTicks();
    void clearDataMap() {curveDataMap.clear();}

    int heightForWidth(int width) const
    {
        return (width*3)/5;
    }
    QSize minimumSizeHint() const
    {
        return QSize(Margin*6,Margin*4);
    }

    QSize sizeHint() const
    {
        return QSize(Margin*12 ,Margin*8);
    }

    void setNoOfTicks(int numX , int numY)
    {
        numXTicks = numX;
        numYTicks = numY;
        this->adjustTicks();
    }

    void setBackgroundColor(QColor color)
    {
        backgroundColor = color;
    }
    void setTextColor(QColor color)
    {
        textColor = color;
    }

    void addColortoMap(QColor color)
    {
        colorMap[colorMap.count()] = color;
    }

    ~Plotter();
signals:
    void maximizeButtonSignal();

private slots:
    void maximizeButtonSlot();
    void changePlotSettingSlot();
    void applyColorSetting(QColor back, QColor text,QColor grid, QVector <QColor> vect);
    void saveSettings();
    void loadSettings();
    void saveAsImage();
    void gridButtonSlot();
private:
    enum { Margin = 50 };
    int noOfCurves;
    int noOfPoints;
    int minY;
    int maxY;
    int numXTicks;
    int numYTicks;
    bool antiAliasing;
    bool showGrid;

    QColor backgroundColor;
    QColor textColor;
    QColor gridColor;
    QPixmap pixmap;
    QMap <int ,QColor> colorMap;
    QMap <int , QList <double>* > curveDataMap;
    QToolButton* maximizeButton;
    QToolButton* curvePenButton;
    QToolButton* savePictureButton;
    QToolButton* gridButton;
};

#endif // PLOTTER_H
