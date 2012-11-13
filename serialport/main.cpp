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
   // qDebug() <<port.getDeviceName();
    port.setReadWrite();
    port.setBaudRate(BAUD38400);
    port.openDevice();
    port.showData();
    port.start();
    //port.applySetting();

//    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
    char ch='q';
//    int readNum;
    cin >> ch;
  //  int num;
    while(ch !='q')
    {
        qDebug() << port.buff.size();
        qDebug() << QString(port.readBytes(100));

//        if((num = port.buff.size()) >0)
//        {
//            qDebug() << QString(port.buff.left(num));
//            port.buff.remove(0,num);
//        }

       // qDebug() << "Reading from STD INPUT" <<ch;
        qDebug() << "writing to port:" <<port.writeToPort(&ch,1);
        cin >> ch;
       // port.hideData();
    }
    qDebug() <<port.readBytes(port.BytesAvailable()).size();
    port.closeDevice();
    std::cin.get();
    return 0;
}
