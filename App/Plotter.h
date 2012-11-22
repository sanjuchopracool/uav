#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMap>
#include <QVector>
#include <QColor>
#include <QToolButton>

class Plotter : public QWidget
{
    Q_OBJECT
    
public:
    Plotter(QWidget *parent = 0);
    void refreshImage();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    QRect printRect();
    void setCurveData(int id , QVector<double>* dataVector, QPen curvePen);
    void setSetting(int no_Curves , int no_Points , int MinY , int MaxY);
    void drawText(QPainter& painter);
    void drawCurves(QPainter& painter);
    void adjustTicks();
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

    ~Plotter();
signals:
    void maximizeButtonSignal();

private slots:
    void maximizeButtonSlot();
private:
    enum { Margin = 50 };
    int noOfCurves;
    int noOfPoints;
    int minY;
    int maxY;
    int numXTicks;
    int numYTicks;
    bool antiAliasing;

    QColor backgroundColor;
    QColor textColor;
    QPixmap pixmap;
    QMap <int ,QPen> colorMap;
    QMap <int , QVector <double>* > curveDataMap;
    QToolButton* maximizeButton;
};

#endif // PLOTTER_H
