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
    port.start();
    //port.applySetting();

//    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
    char ch='q';
//    int readNum;
    cin >> ch;
    while(ch !='q')
    {
       // qDebug() << "Reading from STD INPUT" <<ch;
        qDebug() << "writing to port:" <<port.writeToPort(&ch,1);
        cin >> ch;
    }
    port.closeDevice();
    std::cin.get();
    return 0;
}
