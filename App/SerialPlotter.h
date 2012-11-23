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

class SerialPlotter : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPlotter(QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    void disconnectSignals();
    
signals:
    
public slots:
    void showPlotButtonSlot();
    void maximizeButtonSlot();
    void startPlotButtonSlot();
    void lineReceived(int num);
    void detectNoOfCurves(int num);
    void timeout();
    void closePortSlot();
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
    QLabel* noOfCurvesLabel;
    QLineEdit* noOfCurvesEdit;
    QHBoxLayout* plotSettingLayout;
    QGroupBox* plotSettingGroupBox;
    QPushButton* startPlotButton;

    QVector< QVector <double> > curveData;
    int noOfCurves;
    QTimer *timer;
};

#endif // SERIALPLOTTER_H
