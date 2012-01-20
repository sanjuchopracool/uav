#include "receiveport.h"

ReceivePort::ReceivePort(QextSerialPort *port)
{
    receiveport = port ;
    stopped = false ;  //initially the receiving is disabled
}
void ReceivePort::run()
{
    int numbytes = 0 ;
    char data[1024] ;
    QByteArray receivedData ;
    while(1)
    {
        if(stopped)
        {
            stopped =false ;
            break;
        }
        numbytes = receiveport->bytesAvailable();
        if(numbytes)
        {
            receivemutex.lock();
            receiveport->read(data,numbytes);
            receivedData =data ;
            receivemutex.unlock();
            emit BytesReceived_signal(receivedData);
            qDebug()<<data;
        }
    }

}
void ReceivePort::startReceiving()
{
    stopped =false ;
}
void ReceivePort::stopReceiving()
{
    stopped = true ;
}
