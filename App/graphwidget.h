#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "Plotter.h"
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGroupBox>

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    
signals:
    void maximizeButtonSignal();
public slots:
    void toggleVisibility();
    void startButtonSlot();
    void stopButtonSlot();
    void resizeDataList();
    void lineReceiveSlot(QByteArray);
private:
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
    QPushButton* stopButton;

    QList< QList <double> > curveData;
    int noOfCurves;
    int noOfPoints;
    QIntValidator *intValidator;
    QDoubleValidator* doubleValidator;

    //used for data extraction
    double data;
    char ch;
    bool plotCurve;
    
};

#endif // GRAPHWIDGET_H
