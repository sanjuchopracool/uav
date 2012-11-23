#ifndef SERIALPLOTTER_H
#define SERIALPLOTTER_H
#include "Plotter.h"
#include "SerialApp.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGroupBox>
#include <QPushButton>
static int signalCount = 0;
class SerialPlotter : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPlotter(QWidget *parent = 0);
    void disconnectSignals();
    void resizeCurveVector();
    ~SerialPlotter();
    
signals:
    
public slots:
    void showPlotButtonSlot();
    void maximizeButtonSlot();
    void startPlotButtonSlot();
    void lineReceived(int num);
    void detectNoOfCurves(int num);
    void timeout();
    void closePortSlot();
    void stopButtonSlot();
private:
    SerialApp *app;
    Plotter*plot;
    QVBoxLayout* mainlayout;
    QLabel* noOfPointsLabel;
    QLineEdit* noOfPointsEdit;
    QLabel* minYLabel;
    QLineEdit* minYEdit;
    QLabel* maxYLabel;
    QLineEdit* maxYEdit;
    QHBoxLayout* plotSettingLayout;
    QGroupBox* plotSettingGroupBox;
    QPushButton* startPlotButton;
    QPushButton* stopButton;

    QVector< QVector <double> > curveData;
    int noOfCurves;
    int noOfPoints;
    QTimer *timer;
};

#endif // SERIALPLOTTER_H
