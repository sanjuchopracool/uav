#include <QCoreApplication>
#include "serialport.h"
#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    SerialPort port;
    port.setDeviceName("/dev/ttyACM0");
   // qDebug() <<port.getDeviceName();
    port.setReadWrite();
   // port.setBaudRate(BAUD38400);
    port.openDevice();
    port.showData();
    port.start();
    char ch='q';
    cin >> ch;
    while(ch !='q')
    {
//        qDebug() << port.BytesAvailable();
//        qDebug() << QString(port.readBytes(port.BytesAvailable()));
        qDebug() << "writing to port:" << ch ;
        port.writeToPort(&ch,1);
        cin >> ch;
       // port.hideData();
    }
    port.stopDevice();
//    qDebug() <<port.readBytes(port.BytesAvailable()).size();
    if(!port.closeDevice())
        qDebug() << "Problem closing the thread";
    std::cin.get();
    return 0;
}
