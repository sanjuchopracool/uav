#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QMap>
#include <QPen>
#include <QVector>
#include <QPixmap>

class QToolButton;
class PlotSettings;
class Plotter : public QWidget
{
    Q_OBJECT
public:
    Plotter(QWidget *parent = 0);
    void setPlotSettings(const PlotSettings & settings);
    void setCurveDate(int id , QVector<QPointF>& data, QPen& pen);
    void clearCurve(int id);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
public slots:
    void zoomIn();
    void zoomOut();

private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawGridAndText(QPainter &painter);
    void drawCurves(QPainter &painter);

    enum {Margin = 50};
    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;

    QPixmap pixmap;
    bool rubberBandShown;
    int curZoom;
    QRect rubberBandRect;
    QVector<PlotSettings> zoomStack;         //when user zoom PlotSetting will be saved on this
    QMap<int,QVector <QPointF> > curveMap;  //map to store the curve's data there can be n no of curves
    QColor backgroundColor;
    QMap<int,QPen> penMap;
    QColor textColor;
};
class PlotSettings
{
public:
    PlotSettings();

    void scroll(int dx , int dy);
    void adjust();
    double spanX() const  { return maxX - minX; }
    double spanY() const  { return maxY - minY; }

    double minX;
    double maxX;
    int numXTicks;

    double minY;
    double maxY;
    int numYTicks;

private:
    static void adjustAxis(double &min, double& max,int& numTicks);
};

#endif // PLOTTER_H
