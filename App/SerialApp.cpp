#include "SerialApp.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

Q_DECLARE_METATYPE(BaudRateType)
Q_DECLARE_METATYPE(StopBitsType)
Q_DECLARE_METATYPE(DataBitsType)
Q_DECLARE_METATYPE(ParityType)

void SerialApp::refreshDevices()
{
    QStringList deviceList;
    QDir dir("/dev/");
    QStringList filters;
    filters  << "ttyUSB*" << "ttyS*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files| QDir::System);
    dir.setSorting(QDir::Unsorted);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        deviceList << fileInfo.fileName();
    }
    this->portBox->clear();
    this->portBox->addItems(deviceList);

}

void SerialApp::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt) ;; CSV (*csv)");
    if(fileName.isEmpty())
        return;

    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,"Error in saving","Unable to save the file.\nPlease check file permissions.");
        return;
    }

    QTextStream stream(&saveFile);
    stream << this->textEdit->toPlainText();
    saveFile.close();
}

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
    refreshDevices();

    portBox->setToolTip("click to add custom port");
    portBox->setEditable(true);
    baudBox = new QComboBox;

    baudBox->addItem("50",QVariant::fromValue(BAUD50));
    baudBox->addItem("75",QVariant::fromValue(BAUD75));
    baudBox->addItem("110",QVariant::fromValue(BAUD110));
    baudBox->addItem("134",QVariant::fromValue(BAUD134));
    baudBox->addItem("150",QVariant::fromValue(BAUD150));
    baudBox->addItem("200",QVariant::fromValue(BAUD200));
    baudBox->addItem("300",QVariant::fromValue(BAUD300));
    baudBox->addItem("600",QVariant::fromValue(BAUD600));
    baudBox->addItem("1200",QVariant::fromValue(BAUD1200));
    baudBox->addItem("1800",QVariant::fromValue(BAUD1800));
    baudBox->addItem("2400",QVariant::fromValue(BAUD2400));
    baudBox->addItem("4800",QVariant::fromValue(BAUD4800));
    baudBox->addItem("9600",QVariant::fromValue(BAUD9600));
    baudBox->addItem("19200",QVariant::fromValue(BAUD19200));
    baudBox->addItem("38400",QVariant::fromValue(BAUD38400));
    baudBox->addItem("57600",QVariant::fromValue(BAUD57600));
    baudBox->addItem("115200",QVariant::fromValue(BAUD115200));
    baudBox->addItem("230400",QVariant::fromValue(BAUD230400));
    baudBox->addItem("460800",QVariant::fromValue(BAUD460800));
    baudBox->addItem("500000",QVariant::fromValue(BAUD500000));
    baudBox->addItem("576000",QVariant::fromValue(BAUD576000));
    baudBox->addItem("921600",QVariant::fromValue(BAUD921600));
    baudBox->addItem("1000000",QVariant::fromValue(BAUD1000000));
    baudBox->addItem("1152000",QVariant::fromValue(BAUD1152000));
    baudBox->addItem("1500000",QVariant::fromValue(BAUD1500000));
    baudBox->addItem("2000000",QVariant::fromValue(BAUD2000000));
    baudBox->addItem("2500000",QVariant::fromValue(BAUD2500000));
    baudBox->addItem("3000000",QVariant::fromValue(BAUD3000000));
    baudBox->addItem("3500000",QVariant::fromValue(BAUD3500000));
    baudBox->addItem("4000000",QVariant::fromValue(BAUD4000000));
    baudBox->setCurrentIndex(14);


    dataBitBox = new QComboBox;
    dataBitBox->addItem("5",QVariant::fromValue(DB5));
    dataBitBox->addItem("6",QVariant::fromValue(DB6));
    dataBitBox->addItem("7",QVariant::fromValue(DB7));
    dataBitBox->addItem("8",QVariant::fromValue(DB8));
    dataBitBox->setCurrentIndex(3);

    parityBox = new QComboBox;
    parityBox->addItem("none",QVariant::fromValue(DB5));
    parityBox->addItem("Even",QVariant::fromValue(DB6));
    parityBox->addItem("Odd",QVariant::fromValue(DB7));

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
    refreshButton = new QPushButton("Refresh list");
    showPlotButton = new QToolButton;
    showPlotButton->setToolTip("Show Plot");
    showPlotButton->setIconSize(QSize(75,50));
    showPlotButton->setCheckable(true);
    showPlotButton->setIcon(QIcon(":/images/graph.png"));
    showPlotButton->adjustSize();

    buttonLayout = new QVBoxLayout;
    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(showPlotButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(saveButton);

    textEdit = new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setMinimumWidth(500);
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

    this->closeButton->setDisabled(true);
    this->sendButton->setDisabled(true);
    this->sendEdit->setDisabled(true);
    //settingGroupBox->setDisabled(true);
   // plot->hide();
    //connections
    connect(openButton,SIGNAL(clicked()),this,SLOT(open()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(sendButton,SIGNAL(clicked()),this,SLOT(send()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clear()));
    connect(sendEdit,SIGNAL(returnPressed()),this,SLOT(send()));
    connect(refreshButton,SIGNAL(clicked()),this,SLOT(refreshDevices()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(save()));
    connect(this->showPlotButton,SIGNAL(clicked()),this,SLOT(showPlotButtonSlot()));

}

SerialApp::~SerialApp()
{
}

//void SerialApp::hideControls()
//{
//    settingGroupBox->hide();
//    refreshButton->hide();
//    openButton->hide();
//    gridButton->hide();
//    closeButton->hide();
//    clearButton->hide();
//    saveButton->hide();
//    textEdit->hide();
//    sendButton->hide();
//    sendEdit->hide();
//}

void SerialApp::open()
{

    port.setDeviceName("/dev/" + portBox->currentText());
    if(readPortCheck->isChecked() && writePortCheck->isChecked())
    {
        this->sendButton->setEnabled(true);
        this->sendEdit->setEnabled(true);
        port.setReadWrite();
    }
    else if(readPortCheck->isChecked())
        port.setReadOnly();
    else if(writePortCheck->isChecked())
    {
        this->sendButton->setEnabled(true);
        this->sendEdit->setEnabled(true);
        port.setWriteOnly();
    }
    else
    {
        QMessageBox::information(this,"Port Open","Atleast select one mode for opening port.\n");
        return;
    }

    if(!QFile(port.getDeviceName()).exists())
    {
        QMessageBox::warning(this,"Error opening port",port.getDeviceName() +" does not exists.");
        return;
    }

    if(!port.openDevice())
    {
        QMessageBox::warning(this,"Error opening port","Unable to open port");
        return;
    }

    QVariant temp;
    temp = baudBox->itemData(baudBox->currentIndex());
    port.setBaudRate(temp.value<BaudRateType>());

    temp = dataBitBox->itemData(dataBitBox->currentIndex());
    port.setDataBits(temp.value<DataBitsType>());

    if(parityBox->currentIndex())
    {
        temp = parityBox->itemData(parityBox->currentIndex());
        port.setParity(temp.value<ParityType>());
    }

    if(stopBitCheck->isChecked())
        port.setStopBits(SB2);
    if(!port.applySetting())
    {
        QMessageBox::warning(this,"Error opening port","Unable to apply port setting.");
        return;

    }

    //disabling and enabling
    settingGroupBox->setDisabled(true);
    closeButton->setEnabled(true);
    openButton->setDisabled(true);
    refreshButton->setEnabled(false);

    connect(&port,SIGNAL(signalReceied(QByteArray)),this,SLOT(dataReceived(QByteArray)));
    connect(&port,SIGNAL(lineReceived(int)),this,SIGNAL(lineReceivedApp(int)));
    port.start();
    port.setPriority(QThread::LowestPriority);
    sendEdit->setFocus();

}

void SerialApp::close()
{
    disconnect(&port,SIGNAL(signalReceied(QByteArray)),this,SLOT(dataReceived(QByteArray)));
    disconnect(this->showPlotButton,SIGNAL(clicked()),this,SIGNAL(lineReceivedApp(int)));
    this->port.closeDevice();
    emit closePortSignal();
    this->closeButton->setDisabled(true);
    this->sendButton->setDisabled(true);
    this->sendEdit->setDisabled(true);
    settingGroupBox->setDisabled(false);
    closeButton->setEnabled(false);
    openButton->setDisabled(false);
    refreshButton->setEnabled(true);
}

void SerialApp::send()
{
    char *data;
    QByteArray dataArray = this->sendEdit->text().toAscii();
    data = dataArray.data();
    port.writeToPort(data,dataArray.size());
    this->sendEdit->clear();
}

void SerialApp::dataReceived(QByteArray array)
{
    textEdit->insertPlainText(array);
    textEdit -> moveCursor (QTextCursor::End) ;
}


void SerialApp::showPlotButtonSlot()
{
    if(!showPlotButton->isChecked())
    {
        showPlotButton->setToolTip("Show Plot");
       // this->plot->hide();
    }
    else
    {
        this->showPlotButton->setToolTip("Hide Plot");
      //  this->plot->show();
    }
    emit showPlotButtonSignal();
}
