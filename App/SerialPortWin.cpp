#include "SerialPortWin.h"
#include <cstring>
#include <stdio.h>

SerialPort::SerialPort(QObject *parent) :
    QThread(parent)
{
    initBaudRateList();
    stopThread = true;
    debug = false;
    readFlag = true;
    writeFlag = true;
    dcb.DCBlength = sizeof(dcb);
    openFlags = GENERIC_READ;
}

SerialPort::~SerialPort()
{
    this->stopThread = true;
    this->wait();
    this->terminate();
    this->wait();
    this->closeDevice();
}

bool SerialPort::openDevice()
{
    fileHandle = CreateFile( (LPCWSTR)deviceName.toStdWString().data(),openFlags,0,
                        0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

    if (fileHandle == INVALID_HANDLE_VALUE)
       // error opening port; abort
        return false;
    if(applySetting())
        return true;
    return false;
}


void SerialPort::setParity(ParityType parity)
{
    //if parity is odd or even than enable parity and set it
    if(parity == ODD)
    {
        dcb.fParity = true;
        dcb.Parity = ODDPARITY;
    }
    else if(parity == EVEN)
    {
        dcb.fParity = true;
        dcb.Parity = EVENPARITY;
    }
    else
    {
        dcb.fParity = false;
        dcb.Parity = NOPARITY;
    }
}

bool SerialPort::applySetting()
{
    dcb.DCBlength = sizeof(dcb);
    if(!SetCommState(fileHandle, &dcb)) {
        return false;
    }
    if(!SetupComm(fileHandle,
                  1024,
                  1024))
    {
        return false;
    }

    return true;
}


void SerialPort::setStopBits(unsigned char stopBits)
{
    if(stopBits == 2)
        dcb.StopBits = TWOSTOPBITS;
    else
        dcb.StopBits = ONESTOPBIT;
}


void SerialPort::setDataBits(unsigned char dbits)
{
    switch(dbits)
    {
    case 5:
        dcb.ByteSize = DATABITS_5;
        break;
    case 6:
        dcb.ByteSize = DATABITS_6;
        break;
    case 7:
        dcb.ByteSize = DATABITS_7;
        break;
    default:
        dcb.ByteSize = DATABITS_8;
        break;
    }
}


void SerialPort::setBaudRate(int baud)
{
    if(!baudRateList.contains(baud))
    {
        qDebug() << "Unsuppoerted Baud Rate :" << baud << ", applying 9600 baud rate";
        baud = 9600;
    }
    dcb.BaudRate = baud;
}


QByteArray SerialPort::readBytes(int len)
{
    QByteArray retArray;
    int byte = this->BytesAvailable();
    // mutex.lock();
    if(len <= byte)
    {
        retArray = ReceiveBuff.left(len);
        ReceiveBuff.remove(0,len);
    }
    else
    {
        qDebug() << len <<"bytes are not available";
        retArray = ReceiveBuff.left(byte);
        ReceiveBuff.remove(0,byte);
    }
    // mutex.unlock();
    return retArray;
}

void SerialPort::initBaudRateList()
{
    baudRateList << 110 << 300 << 600 << 1200 << 2400 << 4800
                 << 9600 << 14400 << 19200 << 38400 << 56000 <<
                    57600 << 115200 << 128000 << 256000;
}

QList<int> SerialPort::baudList() const
{
    return baudRateList;
}

void SerialPort::run()
{
    char buffer[4096] ,*charPtr;
    QByteArray array;
//    int numSent = -1, noToSent = -1;
    unsigned long num = -1;
    while(!stopThread)
    {
        if(readFlag)
        {
            mutex.lock();

            /*
*Reading from port
*/

            ReadFile(fileHandle,buffer,1024,&num,NULL);
            if((num != -1) && num)
            {
                ReceiveBuff.append(buffer,num);
                array = QByteArray(buffer,num);
                emit signalReceied(array);
            }
            mutex.unlock();
        }

//        noToSent = ReceiveBuff.indexOf('\n');
//        if(noToSent != -1 && noToSent)
//        {
//            emit lineReceived(readBytes(noToSent + 1));
//        }

//        /*
//*writing to port
//*/

//        num = WriteBuff.size();
//        if(num)
//        {
//            mutex.lock();
//            charPtr = WriteBuff.data();
//            numSent = write(ttyFd,charPtr,num);
//            mutex.unlock();
//            if((numSent != -1) && numSent)
//            {
//                WriteBuff.remove(0,numSent);
//            }
//            else
//                qDebug() <<"Error in writing to port";
//        }


    }
}


void SerialPort::writeToPort(char *buff, int num)
{
    WriteBuff.append(buff,num);
}


void SerialPort::clearSetting()
{
    memset(&dcb,0,sizeof(dcb));
}


bool SerialPort::closeDevice()
{
    if(!CloseHandle(fileHandle))
        return false;
    clearSetting();
    return true;
}


void SerialPort::setReadWrite()
{
    openFlags = GENERIC_READ | GENERIC_WRITE;
    readFlag = true;
    writeFlag = true;
}


void SerialPort::setWriteOnly()
{
    openFlags = GENERIC_WRITE;
    readFlag = false;
    writeFlag = true;
}


void SerialPort::setReadOnly()
{
    openFlags = GENERIC_READ;
    readFlag = true;
    writeFlag=false;
}


void SerialPort::slotReceived(QByteArray array)
{
    qDebug() << QString(array);
}
