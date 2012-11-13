#include "serialport.h"
void printError(const SerialPort* port)
{
    qDebug() << port->getDeviceName()  << " Error: " <<QString(strerror(errno));
}

SerialPort::SerialPort(QObject *parent) :
    QThread(parent)
{
    debug = false;

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

    connect(this,SIGNAL(signalReceied(QByteArray)),this,SLOT(slotReceived(QByteArray)));
}

bool SerialPort::openDevice()
{
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
    applySetting();
    qDebug() << "Successfully opened the device " << this->getDeviceName();
    return true;
}

void SerialPort::setReadOnly()
{
    openFlags |= O_RDONLY;
}

void SerialPort::setWriteOnly()
{
    openFlags |= O_WRONLY;
}

void SerialPort::setReadWrite()
{
    openFlags |= O_RDWR;
}

bool SerialPort::closeDevice()
{
    if(close(ttyFd) == -1)
    {
        printError(this);
        return false;
    }
    qDebug() <<"Successfully closed the device " << this->getDeviceName();
    return true ;
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

void SerialPort::applySetting()
{
//    qDebug() <<ttyFd;
//    qDebug() << config.c_cflag;
    if(ttyFd != -1)
        tcsetattr(ttyFd, TCSANOW, &config);
    else
        qDebug() <<"Error";
}

void SerialPort::clearSetting()
{
    memset(&config,0,sizeof(config));
}

int SerialPort::writeToPort(char *buff, int num)
{
    int bytes=0;
    mutex.lock();
    bytes = write(ttyFd,buff,num);
    if(bytes < num)
        qDebug() << "only" << bytes << "are written";
    mutex.unlock();
    return bytes;
}

QByteArray SerialPort::readBytes(int len)
{
    QByteArray retArray;
    int byte = this->BytesAvailable();
    mutex.lock();
    if(len <= byte)
    {
        retArray = buff.left(len);
        buff.remove(0,len);
    }
    else
    {
        qDebug() << len <<"bytes are not available";
        retArray = buff.left(byte);
        buff.remove(0,byte);
    }
    mutex.unlock();
    return retArray;
}

void SerialPort::run()
{
    char buffer[4096] ;
    QByteArray array;
    int num = 0;
    forever
    {
        mutex.lock();
        num = read(ttyFd,buffer,4096);
        if((num != -1) && num)
        {
            emit signalReceied(QByteArray(buffer,num));
            buff.append(buffer,num);
            if(debug)
                write(STDOUT_FILENO,buffer,num);
        }
        mutex.unlock();
    }

}


void SerialPort::slotReceived(QByteArray array)
{
    qDebug() << QString(array);

}


/*
 *Method to remove data from
 *
    QByteArray array("sanjuchopracool");
    QByteArray read;
    read = array.left(5);   //read = "sanju"
    array.remove(0,5);     // array = "chopracool"
 */
