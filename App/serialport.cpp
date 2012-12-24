#include "serialport.h"
void printError(const SerialPort* port)
{
    qDebug() << port->getDeviceName()  << " Error: " <<QString(strerror(errno));
}

SerialPort::SerialPort(QObject *parent) :
    QThread(parent)
{
    stopThread = true;
    debug = false;
    readFlag = true;
    writeFlag = true;
    ttyFd = -1 ;   //by default fd should be -1
    deviceName = "/dev/ttyUSB0" ;               //default is ttyUSB0 my laptop does not have ttyso
    openFlags = O_NONBLOCK | O_NOCTTY ;         //use non blocking (used for terminal , fifi ,sockets),and
                                                //no control terminal for process

    /*
     *make sure config struct is filled with zero
     */


    memset(&config,0,sizeof(config));
    config.c_cc[VMIN]=0;
    config.c_cc[VTIME]=0;
    config.c_iflag=0;
    config.c_oflag=0;
    config.c_lflag=0;

    /*
     *set the control flags for config
     *enable Receiving and don't change ownership
     *default size 8
     *baud rate 9600
     */


    config.c_cflag = CREAD | CLOCAL | CS8 | B9600;
}

bool SerialPort::openDevice()
{
    bool ret = false;
    openFlags |= O_NONBLOCK | O_NOCTTY ;
    ttyFd = open(&deviceName[0],openFlags);
    if(ttyFd == -1)
    {
        printError(this);
        return false ;
    }


    /*
     *set tty flag such that idoes not wait when we use read function
     */



    fcntl(ttyFd,F_SETFL,O_NONBLOCK);
    ret = applySetting();
    if(ret)
    {
        qDebug() << "Successfully opened the device" << this->getDeviceName();
        return ret;
    }

    qDebug() << "Unable to apply terminal setting";
    return false;
}

void SerialPort::setReadOnly()
{
    openFlags = O_RDONLY;
    readFlag = true;
    writeFlag=false;
}

void SerialPort::setWriteOnly()
{
    openFlags = O_WRONLY;
    readFlag = false;
    writeFlag = true;
}

void SerialPort::setReadWrite()
{
    openFlags = O_RDWR;
    readFlag = true;
    writeFlag = true;
}

bool SerialPort::closeDevice()
{
    if(ttyFd == -1)
        return false;
    if(close(ttyFd) == -1)
    {
        printError(this);
        return false;
    }
    ttyFd = -1;
    qDebug() <<"Successfully closed the thread for device" << this->getDeviceName();
    return true;
}

void SerialPort::setBaudRate(enum BaudRateType baud)
{
    //make sure to use bit wise operation
#ifndef CBAUD
#define CBAUD 0010017
#endif
    config.c_cflag &= (~CBAUD);

    switch (baud) {
    case BAUD50:
        config.c_cflag |= B50;
        break;
    case BAUD75:
        config.c_cflag |= B75;
        break;
    case BAUD110:
        config.c_cflag |= B110;
        break;
    case BAUD134:
        config.c_cflag |= B134;
        break;
    case BAUD150:
        config.c_cflag |= B150;
        break;
    case BAUD200:
        config.c_cflag |= B200;
        break;
    case BAUD300:
        config.c_cflag |= B300;
        break;
    case BAUD600:
        config.c_cflag |= B600;
        break;
    case BAUD1200:
        config.c_cflag |= B1200;
        break;
    case BAUD1800:
        config.c_cflag |= B1800;
        break;
    case BAUD2400:
        config.c_cflag |= B2400;
        break;
    case BAUD4800:
        config.c_cflag |= B4800;
        break;
    case BAUD9600:
        config.c_cflag |= B9600;
        break;
    case BAUD19200:
        config.c_cflag |= B19200;
        break;
    case BAUD38400:
        config.c_cflag |= B38400;
        break;
    case BAUD57600:
        config.c_cflag |= B57600;
        break;
    case BAUD115200:
        config.c_cflag |= B115200;
        break;
    case BAUD230400:
        config.c_cflag |= B230400;
        break;
    case BAUD460800:
        config.c_cflag |= B460800;
        break;
    case BAUD500000:
        config.c_cflag |= B500000;
        break;
    case BAUD576000:
        config.c_cflag |= B576000;
        break;
    case BAUD921600:
        config.c_cflag |= B921600;
        break;
    case BAUD1000000:
        config.c_cflag |= B1000000;
        break;
    case BAUD1152000:
        config.c_cflag |= B1152000;
        break;
    case BAUD1500000:
        config.c_cflag |= B1500000;
        break;
    case BAUD2000000:
        config.c_cflag |= B2000000;
        break;
    case BAUD2500000:
        config.c_cflag |= B2500000;
        break;
    case BAUD3000000:
        config.c_cflag |= B3000000;
        break;
    case BAUD3500000:
        config.c_cflag |= B3500000;
        break;
    case BAUD4000000:
        config.c_cflag |= B4000000;
        break;
    default:
        break;
    }
}

void SerialPort::setDataBits(DataBitsType dbits)
{
#ifndef  CSIZE
#define  CSIZE  0000060
#endif
    config.c_cflag &= (~CSIZE);

    switch(dbits)
    {
    case DB5:
        config.c_cflag |= CS5;
        break;
    case DB6:
        config.c_cflag |= CS6;
        break;
    case DB7:
        config.c_cflag |= CS7;
        break;
    case DB8:
        config.c_cflag |= CS8;
        break;
    default:
        break;
    }

}

void SerialPort::setStopBits(StopBitsType stopBits)
{
    config.c_cflag &= (~CSTOPB);
    switch(stopBits)
    {
    case SB2:
        config.c_cflag |= CSTOPB;
        break;
    default:
        break;
    }
}

void SerialPort::setParity(ParityType parity)
{
    config.c_cflag |= PARENB ;  //enable parity by default even parity
    if(parity == ODD)
        config.c_cflag |= PARODD;
}

bool SerialPort::applySetting()
{
    if(ttyFd != -1)
    {
        mutex.lock();
        if(tcsetattr(ttyFd, TCSANOW, &config) == 0)
        {
            mutex.unlock();
            return true;
        }
        mutex.unlock();
    }
    printError(this);
    return false;
}

void SerialPort::clearSetting()
{
    memset(&config,0,sizeof(config));
}

void SerialPort::writeToPort(char *buff, int num)
{
    WriteBuff.append(buff,num);
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

void SerialPort::run()
{
    char buffer[4096] ,*charPtr;
    QByteArray array;
    int num = 0, numSent=0,noToSent=0;
    while(!stopThread)
    {
        if(readFlag)
        {
            mutex.lock();

            /*
         *Reading from port
         */

            num = read(ttyFd,buffer,4096);
            if((num != -1) && num)
            {
                ReceiveBuff.append(buffer,num);
                array = QByteArray(buffer,num);
                emit signalReceied(array);
                if(debug)
                    write(STDOUT_FILENO,buffer,num);
            }
            mutex.unlock();
        }

        noToSent = ReceiveBuff.indexOf('\n');
        if(noToSent != -1)
            emit lineReceived(noToSent);

        /*
         *writing to port
         */

        num = WriteBuff.size();
        if(num)
        {
            mutex.lock();
            charPtr = WriteBuff.data();
            numSent = write(ttyFd,charPtr,num);
            mutex.unlock();
            if((numSent != -1) && numSent)
            {
                WriteBuff.remove(0,numSent);
            }
            else
                qDebug() <<"Error in writing to port";
        }


    }

}


void SerialPort::slotReceived(QByteArray array)
{
    qDebug() << QString(array);

}

SerialPort::~SerialPort()
{
    this->stopThread = true;
    this->wait();
    this->terminate();
    this->wait();
    this->closeDevice();
}

/*
 *Method to remove data from
 *
    QByteArray array("sanjuchopracool");
    QByteArray read;
    read = array.left(5);   //read = "sanju"
    array.remove(0,5);     // array = "chopracool"
 */
