#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <termio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <QObject>
#include <QThread>
#include <QMutex>

enum BaudRateType
{
    BAUD0,
    BAUD50,
    BAUD75,
    BAUD110,
    BAUD134,
    BAUD150,
    BAUD200,
    BAUD300,
    BAUD600,
    BAUD1200,
    BAUD1800,
    BAUD2400,
    BAUD4800,
    BAUD9600,
    BAUD19200,
    BAUD38400,
    BAUD57600,
    BAUD115200,
    BAUD230400,
    BAUD460800,
    BAUD500000,
    BAUD576000,
    BAUD921600,
    BAUD1000000,
    BAUD1152000,
    BAUD1500000,
    BAUD2000000,
    BAUD2500000,
    BAUD3000000,
    BAUD3500000,
    BAUD4000000

};
enum DataBitsType
{
    DB5,
    DB6,
    DB7,
    DB8
};

enum StopBitsType
{
    SB1,
    SB2
};

enum ParityType
{
    ODD,
    EVEN
};

class SerialPort : public QThread
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    void setDeviceName(QString name)
    {
        deviceName = name.toStdString();
    }
    QString getDeviceName() const
    {
        return QString::fromStdString(deviceName);
    }
    bool openDevice();
    void setReadOnly();
    void setWriteOnly();
    void setReadWrite();
    bool closeDevice();
    void setBaudRate(BaudRateType baud);
    void setDataBits(DataBitsType dbits);
    void setStopBits(StopBitsType stopBits);
    void setParity(ParityType parity);
    bool applySetting();
    void clearSetting();
    void writeToPort(char* ReceiveBuff,int num);
    QByteArray  readBytes(int len);
    void showData() {debug = true;  }
    void hideData() {debug = false; }
    void stopDevice() {stopThread = false; this->wait();}
    int BytesAvailable() const
    {
        return this->ReceiveBuff.size();
    }


protected:
    void run();

signals:
    void signalReceied(QByteArray);
    void lineReceived(int);
public slots:
    void slotReceived(QByteArray);

private:
    std::string deviceName;
    int ttyFd;
    int openFlags;
    struct termios config;
    QMutex mutex;
    bool debug;
    QByteArray ReceiveBuff;
    QByteArray WriteBuff;
    bool stopThread;
    bool readFlag,writeFlag;

};

#endif // SERIALPORT_H
