#include <QtCore/QCoreApplication>
#include"receiveport.h"
//#include<qextserialport.h>
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QextSerialPort *port =new QextSerialPort ;
    port->setBaudRate(BAUD19200);
    port->setDataBits(DATA_8);
    port->setFlowControl(FLOW_OFF);
    port->setStopBits(STOP_1);
    port->setParity(PAR_NONE);
    if(port->open(QIODevice::ReadWrite))
        qDebug()<<"Successfully opened the port";
    else
        qDebug()<<"Failed";
    ReceivePort *myport =new ReceivePort(port);
    myport->startReceiving();
    myport->start();
    return a.exec();
}
