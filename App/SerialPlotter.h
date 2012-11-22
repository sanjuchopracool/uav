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
    
signals:
    
public slots:
    void showPlotButtonSlot();
    void maximizeButtonSlot();
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
    
};

#endif // SERIALPLOTTER_H
