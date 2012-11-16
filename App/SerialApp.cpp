#include "SerialApp.h"
#include <QDebug>
SerialApp::SerialApp(QWidget *parent)
    : QWidget(parent)
{
    portLabel = new QLabel("Select Port");
    baudLabel = new QLabel("Baud Rate");
    dataBitLabel = new QLabel("Data Bits");
    parityLabel = new QLabel("Parity");
    stopBitCheck = new QCheckBox("Use 2 Stop Bits");
    stopBitCheck->setToolTip("By default use 1 Stop Bit");

    portBox = new QComboBox;
    portBox->setToolTip("click to add custom port");
    portBox->setEditable(true);
    baudBox = new QComboBox;
    dataBitBox = new QComboBox;
    parityBox = new QComboBox;
    readPortCheck = new QCheckBox("Read");
    writePortCheck = new QCheckBox("Write");
    readPortCheck->setChecked(true);
    writePortCheck->setChecked(true);

    settingLayout = new QGridLayout;
    settingGroupBox = new QGroupBox("Serial Setting");

    settingLayout->addWidget(portLabel,0,0);
    settingLayout->addWidget(portBox,0,1);
    settingLayout->addWidget(baudLabel,1,0);
    settingLayout->addWidget(baudBox,1,1);
    settingLayout->addWidget(dataBitLabel,2,0);
    settingLayout->addWidget(dataBitBox,2,1);
    settingLayout->addWidget(parityLabel,3,0);
    settingLayout->addWidget(parityBox,3,1);
    settingLayout->addWidget(stopBitCheck,4,0,1,2);
    settingLayout->addWidget(readPortCheck);
    settingLayout->addWidget(writePortCheck);
    settingGroupBox->setLayout(settingLayout);
    settingGroupBox->setMinimumHeight(275);

    openButton = new QPushButton("Open");
    closeButton = new QPushButton("Close");
    clearButton = new QPushButton("Clear");
    saveButton = new QPushButton("Save");
    buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(saveButton);

    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    sendEdit = new QLineEdit;
    sendButton = new QPushButton("Send");
    sendWidgetLayout = new QHBoxLayout;
    sendWidgetLayout->addWidget(sendEdit);
    sendWidgetLayout->addWidget(sendButton);
    textLayout = new QVBoxLayout;
    textLayout->addWidget(textEdit);
    textLayout->addLayout(sendWidgetLayout);


    upperLeftHLayout = new QHBoxLayout;
    upperleftVLayout = new QVBoxLayout;
    upperLeftHLayout->addWidget(settingGroupBox);
    upperLeftHLayout->addLayout(buttonLayout);
    upperleftVLayout->addLayout(upperLeftHLayout);
    upperleftVLayout->addStretch();
    upperMainLayout = new QHBoxLayout;
    upperMainLayout->addLayout(upperleftVLayout);
    upperMainLayout->addLayout(textLayout);
    this->setLayout(upperMainLayout);

    QStringList list;
    list << "B1200" << "B1400" << "B4100";
    //dummy add
    portBox->addItems(list);
    baudBox->addItems(list);
    settingGroupBox->setDisabled(true);

}

SerialApp::~SerialApp()
{
    
}
