#include <QCoreApplication>
#include "serialport.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    SerialPort port;
   // qDebug() <<port.getDeviceName();
    port.setReadWrite();
    port.setBaudRate(BAUD38400);
    port.openDevice();
    port.applySetting();

//    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
    char buff[4*1024] ,ch='q';
    int readNum;
    cin >> ch;
    while(ch !='q')
    {
       // qDebug() << "Reading from STD INPUT" <<ch;
//        qDebug() << "writing to port:" <<;
        port.writeToPort(&ch,1);
        readNum = port.readFromPort(buff,4096);
        qDebug() << "Read No = "<< readNum;
        cin >> ch;
    }
    port.closeDevice();
    qDebug() <<QString(buff);
    std::cin.get();
    return 0;
}
