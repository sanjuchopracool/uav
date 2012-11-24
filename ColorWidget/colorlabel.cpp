#include "colorlabel.h"
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>

ColorLabel::ColorLabel(QWidget *parent, QColor color) :
    QLabel(parent)
{
    this->setMinimumSize(30,30);
    this->setFixedSize(30,30);
    this->m_Color = color;
}

void ColorLabel::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    painter->setPen(QPen(Qt::white));
    painter->setBrush(m_Color);
    painter->drawRect(this->rect());
    delete painter;
}

void ColorLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        QColor color = QColorDialog::getColor(m_Color,this);
        this->setColor(color);
    }

}
