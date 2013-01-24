#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QDialog>
#include "colorlabel.h"
#include <QVector>
#include <QGridLayout>
namespace Ui {
class ColorWidget;
}

class ColorWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();
    void getColor(QColor back, QColor text,QColor grid, QVector<QColor> *vect);

public slots:
    void applyButtonSlot();
signals:
    void setColor(QColor back,QColor text,QColor grid,QVector<QColor>);
private:
    Ui::ColorWidget *ui;
    QVector<QColor>* colorVector;
    QLabel* colorTextLabel;
    ColorLabel* m_ColorLabel;
    QGridLayout* layout;
    QVector<ColorLabel*>* ptrVector;

};

#endif // COLORWIDGET_H
