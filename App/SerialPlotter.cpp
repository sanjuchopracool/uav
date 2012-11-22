#include "SerialPlotter.h"

SerialPlotter::SerialPlotter(QWidget *parent) :
    QWidget(parent)
{
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
    plotSettingGroupBox->setMaximumHeight(50);

    mainlayout->addWidget(app);
    mainlayout->addWidget(plotSettingGroupBox);
    mainlayout->addWidget(plot);
    this->setLayout(mainlayout);

    plot->hide();
    plotSettingGroupBox->hide();

    connect(app,SIGNAL(showPlotButtonSignal()),this,SLOT(showPlotButtonSlot()));
    connect(plot,SIGNAL(maximizeButtonSignal()),this,SLOT(maximizeButtonSlot()));
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
