#include "receiveport.h"

ReceivePort::ReceivePort(QextSerialPort *port)
{
    receiveport = port ;
}
void ReceivePort::run()
{
    int numbytes =0 ;
    char data[1024] ;
    QByteArray receivedData ;
    while(1)
    {
        numbytes = receiveport->bytesAvailable();
        if(numbytes)
        {
            receivemutex.lock();
            receiveport->read(data,numbytes);
            receivedData =data ;
            receivemutex.unlock();
            emit BytesReceived_signal(receivedData,numbytes);
           // qDebug()<<data;
        }
    }

}
ReceivePort::~ReceivePort()
{
    this->terminate();
    this->wait();
}
