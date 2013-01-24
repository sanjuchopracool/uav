#ifndef SERIALPORTWIN_H
#define SERIALPORTWIN_H

#include <QThread>
#include <Windows.h>
#include <QMutex>
#include <QList>
#include <QDebug>

/* supported baud rates in windows
    #define CBR_110             110
    #define CBR_300             300
    #define CBR_600             600
    #define CBR_1200            1200
    #define CBR_2400            2400
    #define CBR_4800            4800
    #define CBR_9600            9600
    #define CBR_14400           14400
    #define CBR_19200           19200
    #define CBR_38400           38400
    #define CBR_56000           56000
    #define CBR_57600           57600
    #define CBR_115200          115200
    #define CBR_128000          128000
    #define CBR_256000          256000
*/
enum ParityType
{
    NONE,
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
        deviceName = name;
    }

    QString getDeviceName() const
    {
        return deviceName;
    }

    bool openDevice();
    void setReadOnly();
    void setWriteOnly();
    void setReadWrite();
    bool closeDevice();
    void setBaudRate(int baud);
    void setDataBits(unsigned char dbits);
    void setStopBits(unsigned char stopBits);
    void setParity(ParityType parity);
    bool applySetting();
    void clearSetting();
    void writeToPort(char* buff, int num);
    QByteArray readBytes(int len);
    void initBaudRateList();
    QList<int>  baudList() const;

    void showData()
    {
        debug = true;
    }

    void hideData()
    {
        debug = false;
    }

    void stopDevice()
    {
        stopThread = false;
        this->wait();
    }

    int BytesAvailable() const
    {
        return this->ReceiveBuff.size();
    }

    void startThread()
    {
        stopThread =false;
    }

    void clearBuff()
    {
        this->ReceiveBuff.clear();
    }

protected:
    void run();

signals:
    void signalReceied(QByteArray);
    void lineReceived(QByteArray);
public slots:
    void slotReceived(QByteArray array);

private:
    QString deviceName;
    HANDLE fileHandle;
    long int openFlags;
    DCB dcb;
    QMutex mutex;
    bool debug;
    QByteArray ReceiveBuff;
    QByteArray WriteBuff;
    bool stopThread;
    bool readFlag,writeFlag;
    QList<int> baudRateList;
};

#endif // SERIALPORTWIN_H
