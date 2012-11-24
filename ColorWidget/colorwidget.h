#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include "colorlabel.h"
#include <QVector>
#include <QGridLayout>
namespace Ui {
class ColorWidget;
}

class ColorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();

public slots:
    
private:
    Ui::ColorWidget *ui;
    QVector<QColor>* colorVector;
    QLabel* colorTextLabel;
    ColorLabel* m_ColorLabel;
    QGridLayout* layout;
    QVector<ColorLabel*>* ptrVector;

};

#endif // COLORWIDGET_H
