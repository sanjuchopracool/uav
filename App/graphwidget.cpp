#include "graphwidget.h"
#include "SerialApp.h"
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent)
{
    noOfCurves = 0;
    timer =new QTimer;
    timer->setInterval(25);
    mainlayout = new QVBoxLayout;
    this->plot = new Plotter;
    plot->setMinimumHeight(300);

    noOfPointsEdit = new QLineEdit;
    noOfPointsLabel=new QLabel("No. of Points");
    noOfPointsEdit->setText("1000");
    intValidator = new QIntValidator;
    noOfPointsEdit->setValidator(intValidator);

    doubleValidator = new QDoubleValidator;
    minYLabel = new QLabel("Min Y");
    minYEdit = new QLineEdit("-300");
    minYEdit->setValidator(doubleValidator);


    maxYLabel = new QLabel("Max Y");
    maxYEdit = new QLineEdit("300");
    maxYEdit->setValidator(doubleValidator);

    noOfCurvesLabel = new QLabel("No.of Curves");
    noOfCurvesEdit = new QLineEdit("2");
    noOfCurvesEdit->setValidator(intValidator);

    startPlotButton = new QPushButton("Start");
    stopButton = new QPushButton("Stop");

    plotSettingGroupBox = new QGroupBox("Plot Setting");
    plotSettingLayout = new QHBoxLayout;
    plotSettingLayout->addWidget(noOfPointsLabel);
    plotSettingLayout->addWidget(noOfPointsEdit);
    plotSettingLayout->addWidget(minYLabel);
    plotSettingLayout->addWidget(minYEdit);
    plotSettingLayout->addWidget(maxYLabel);
    plotSettingLayout->addWidget(maxYEdit);
    plotSettingLayout->addWidget(noOfCurvesLabel);
    plotSettingLayout->addWidget(noOfCurvesEdit);
    plotSettingLayout->addWidget(startPlotButton);
    plotSettingLayout->addWidget(stopButton);
    stopButton->setEnabled(false);

    plotSettingGroupBox->setLayout(plotSettingLayout);
    plotSettingGroupBox->setMaximumHeight(80);

    mainlayout->addWidget(plotSettingGroupBox);
    mainlayout->addWidget(plot);
    this->setLayout(mainlayout);

    plotCurve = false;

    connect(plot,SIGNAL(maximizeButtonSignal()),this,SIGNAL(maximizeButtonSignal()));

    connect(startPlotButton,SIGNAL(clicked()),this,SLOT(startButtonSlot()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopButtonSlot()));

}

void GraphWidget::toggleVisibility()
{
    if(this->isVisible())
        this->setVisible(false);
    else
        this->setVisible(true);
}

void GraphWidget::startButtonSlot()
{
    plotCurve = true;
    noOfCurves = noOfCurvesEdit->text().toInt();
    noOfPoints = noOfPointsEdit->text().toInt();
    if(noOfCurves < 0) noOfCurves = 0;
    if(noOfPoints < 0) noOfPoints = 0;

    resizeDataList();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    noOfCurvesEdit->setEnabled(false);
    noOfPointsEdit->setEnabled(false);
    maxYEdit->setEnabled(false);
    minYEdit->setEnabled(false);

    startPlotButton->setEnabled(false);
    stopButton->setEnabled(true);
    timer->start();
}

void GraphWidget::stopButtonSlot()
{
    plotCurve = false;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    noOfCurvesEdit->setEnabled(true);
    noOfPointsEdit->setEnabled(true);
    maxYEdit->setEnabled(true);
    minYEdit->setEnabled(true);

    startPlotButton->setEnabled(true);
    stopButton->setEnabled(false);
    timer->stop();
}

void GraphWidget::resizeDataList()
{
    this->curveData.clear();
    this->plot->clearDataMap();
    for(int i = 0 ; i < noOfCurves; i++)
        curveData.insert(i,QList<double>());

    for(int i = 0 ; i < noOfCurves ; i++)
    {
        //curveData[i].clear();
        for( int j = 0; j < noOfPoints ;j++)
            curveData[i].insert(j,0);
    }

    plot->setSetting(noOfCurves,noOfPoints,minYEdit->text().toInt(),maxYEdit->text().toInt());

    for(int i = 0 ; i < noOfCurves ; i++)
    {
        plot->setCurveData(i,&curveData[i]);
    }
}


void GraphWidget::timeout()
{
    this->update();
}

void GraphWidget::lineReceiveSlot(QByteArray dataBytes)
{
    if(plotCurve)
    {
        //qDebug() << dataBytes;
        QTextStream dataStream(dataBytes);
        for(int i = 0 ; i < noOfCurves ; i++)
        {
            dataStream >> data >> ch;
            curveData[i].pop_front();
            curveData[i].append(data);
            //qDebug() << data;
        }
    }
}
