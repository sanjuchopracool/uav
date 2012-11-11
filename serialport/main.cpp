#include <QCoreApplication>
#include "serialport.h"
int main(int argc, char *argv[])
{
    SerialPort port;
   // qDebug() <<port.getDeviceName();
    port.setReadWrite();;
    port.openDevice();
    port.closeDevice();
    return 0;
}
