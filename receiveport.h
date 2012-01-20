#ifndef RECEIVEPORT_H
#define RECEIVEPORT_H
//#include "files/qextserialport.h"
#include<qextserialport.h>
#include <QMutex>
#include<QDebug>
#include<QThread>
class ReceivePort :public QThread
{
    Q_OBJECT
private:

    bool stopped ;
    QextSerialPort *receiveport ;
    QMutex receivemutex ;

public:
    ReceivePort(QextSerialPort *port);
    void stopReceiving();
    void startReceiving();

protected:
    void run();
signals:
    void BytesReceived_signal(const QByteArray &data);
};

#endif // RECEIVEPORT_H
