#include "SerialPlotter.h"
#include <QTextStream>
#include <QTimer>

SerialPlotter::SerialPlotter(QWidget *parent) :
    QWidget(parent)
{
    timer =new QTimer;
    timer->setInterval(50);
    mainlayout = new QVBoxLayout;
    this->plot = new Plotter;
    plot->setMinimumHeight(300);
    this->app = new SerialApp;

    noOfPointsEdit = new QLineEdit;
    noOfPointsLabel=new QLabel("No. of Points");
    noOfPointsEdit->setText("100");
    QIntValidator *intValidator = new QIntValidator;
    noOfPointsEdit->setValidator(intValidator);

    QDoubleValidator* doubleValidator = new QDoubleValidator;
    minYLabel = new QLabel("Min Y");
    minYEdit = new QLineEdit("0");
    minYEdit->setValidator(doubleValidator);


    maxYLabel = new QLabel("Max Y");
    maxYEdit = new QLineEdit("100");
    maxYEdit->setValidator(doubleValidator);

    noOfCurvesLabel = new QLabel("No. of Curves");
    noOfCurvesEdit = new QLineEdit("1");
    noOfCurvesEdit->setValidator(intValidator);

    startPlotButton = new QPushButton("Start");

    plotSettingGroupBox = new QGroupBox("Plot Setting");
    plotSettingLayout = new QHBoxLayout;
    plotSettingLayout->addWidget(noOfCurvesLabel);
    plotSettingLayout->addWidget(noOfCurvesEdit);
    plotSettingLayout->addWidget(noOfPointsLabel);
    plotSettingLayout->addWidget(noOfPointsEdit);
    plotSettingLayout->addWidget(minYLabel);
    plotSettingLayout->addWidget(minYEdit);
    plotSettingLayout->addWidget(maxYLabel);
    plotSettingLayout->addWidget(maxYEdit);
    plotSettingLayout->addWidget(startPlotButton);

    plotSettingGroupBox->setLayout(plotSettingLayout);
    plotSettingGroupBox->setMaximumHeight(80);

    mainlayout->addWidget(app);
    mainlayout->addWidget(plotSettingGroupBox);
    mainlayout->addWidget(plot);
    this->setLayout(mainlayout);

   // plot->hide();
   // plotSettingGroupBox->hide();

    connect(app,SIGNAL(showPlotButtonSignal()),this,SLOT(showPlotButtonSlot()));
    connect(plot,SIGNAL(maximizeButtonSignal()),this,SLOT(maximizeButtonSlot()));
    connect(startPlotButton,SIGNAL(clicked()),this,SLOT(startPlotButtonSlot()));
}

void SerialPlotter::closeEvent(QCloseEvent *)
{
    this->disconnectSignals();
    this->app->~SerialApp();
    this->plot->~Plotter();
}

void SerialPlotter::showPlotButtonSlot()
{
    if(plot->isVisible())
    {
        plotSettingGroupBox->hide();
        plot->hide();
    }
    else
    {
        plotSettingGroupBox->show();
        plot->show();
    }
}

void SerialPlotter::maximizeButtonSlot()
{
    if(this->app->isVisible())
    {
        app->hide();
    }
    else
        app->show();
}

void SerialPlotter::startPlotButtonSlot()
{
    int nCurve = noOfCurvesEdit->text().toInt(),nPoints = noOfPointsEdit->text().toInt();
    if(nCurve < 0 ) nCurve = 0;
    if(nPoints < 0) nPoints = 1;
    this->plot->setSetting(nCurve,nPoints,
                           minYEdit->text().toDouble(),maxYEdit->text().toDouble());
    noOfCurves = nCurve;
    curveData.clear();
    curveData.resize(nCurve);
    for(int i = 0 ; i < noOfCurves ; i++)
    {
        curveData[i].clear();
        curveData[i].resize(nPoints);
    }

    for(int i = 0 ; i < noOfCurves ; i++)
    {
        plot->setCurveData(i,&curveData[i],QPen(Qt::blue));
    }
    connect(app,SIGNAL(lineReceivedApp(int)),this,SLOT(detectNoOfCurves(int)));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    connect(app,SIGNAL(closePortSignal()),this,SLOT(closePortSlot()));
}

void SerialPlotter::lineReceived(int num)
{
    if(app->port.BytesAvailable() >= num+1)
    {
        QByteArray temp = app->port.readBytes(num + 1);
        QTextStream dataStream(temp);
        double data;
        char ch;
        for(int i = 0 ; i < noOfCurves ; i++)
        {
            dataStream >> data >> ch;
            curveData[i].pop_front();
            curveData[i].append(data);
        }
    }
}

void SerialPlotter::detectNoOfCurves(int num)
{
    if(app->port.BytesAvailable() >= num+1)
    {
        QByteArray temp = app->port.readBytes(num + 1);
        QTextStream dataStream(temp);
        double data;
        char ch;
        int i=0;
        for(i = 0 ; ; i++)
        {
            dataStream >> data >> ch;
            if(ch == '\n')
                break;
            curveData[i].pop_front();
            curveData[i].append(data);
        }
        qDebug() << "No of curves detected are: " <<i;
    }

    disconnect(app,SIGNAL(lineReceivedApp(int)),this,SLOT(detectNoOfCurves(int)));
    connect(app,SIGNAL(lineReceivedApp(int)),this,SLOT(lineReceived(int)));

}

void SerialPlotter::timeout()
{
    if(plot->isVisible())
        this->plot->update();
}

void SerialPlotter::closePortSlot()
{
    this->disconnectSignals();
}

void SerialPlotter::disconnectSignals()
{
    disconnect(app,SIGNAL(lineReceivedApp(int)),this,SLOT(lineReceived(int)));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    disconnect(app,SIGNAL(closePortSignal()),this,SLOT(closePortSlot()));
}
