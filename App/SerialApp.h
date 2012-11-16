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
#include <QTextEdit>

class SerialApp : public QWidget
{
    Q_OBJECT
    
public:
    SerialApp(QWidget *parent = 0);
    ~SerialApp();

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

    QPushButton* sendButton;
    QLineEdit* sendEdit;
    QTextEdit* textEdit;
    QCheckBox* readPortCheck;
    QCheckBox* writePortCheck;

    QHBoxLayout* upperLeftHLayout;
    QVBoxLayout* upperleftVLayout;
    QHBoxLayout* upperMainLayout;
    QVBoxLayout* buttonLayout;
    QVBoxLayout* textLayout;
    QHBoxLayout* sendWidgetLayout;
};

#endif // SERIALAPP_H
