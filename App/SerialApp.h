#ifndef SERIALAPP_H
#define SERIALAPP_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include "serialport.h"
#include <QSplitter>
#include <QToolButton>

class SerialApp : public QWidget
{
    Q_OBJECT
    
public:
    SerialApp(QWidget *parent = 0);
    ~SerialApp();
    SerialPort* instance()  { return &port;}

public slots:
    void open();
    void close();
    void send();
    void dataReceived(QByteArray array);
    void clear() {this->textEdit->clear();}
    void refreshDevices();
    void save();
    void showPlotButtonSlot();
    void toogleVisibility();

signals:
    void showPlotButtonSignal();
    void lineReceivedApp(QByteArray);
    void closePortSignal();
private:
    QLabel* portLabel;
    QLabel* baudLabel;
    QLabel* dataLabel;
    QLabel* dataBitLabel;
    QLabel* parityLabel;

    QComboBox* portBox;
    QComboBox* baudBox;
    QComboBox* dataBitBox;
    QComboBox* parityBox;

    QCheckBox* stopBitCheck;
    QGridLayout* settingLayout;
    QGroupBox* settingGroupBox;

    QPushButton* openButton;
    QPushButton* closeButton;
    QPushButton* clearButton;
    QPushButton* saveButton;
    QPushButton* refreshButton;

    QPushButton* sendButton;
    QLineEdit* sendEdit;
    QPlainTextEdit* textEdit;
    QCheckBox* readPortCheck;
    QCheckBox* writePortCheck;

    QHBoxLayout* upperLeftHLayout;
    QVBoxLayout* upperleftVLayout;
    QHBoxLayout* upperMainLayout;
    QVBoxLayout* buttonLayout;
    QVBoxLayout* textLayout;
    QHBoxLayout* sendWidgetLayout;
//    QVBoxLayout* mainLayout;
    QToolButton* showPlotButton;

public:
    static SerialPort port;
//    Plotter* plot;
};

#endif // SERIALAPP_H
