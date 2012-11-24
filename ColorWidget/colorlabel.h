#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QColor>

class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ColorLabel(QWidget *parent = 0,QColor color=QColor());
    void setColor(QColor color) {m_Color = color;}
    QColor color() const {return m_Color;}
    QString getName() const  {return m_Color.name();}
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    
signals:
    
public slots:
private:
    QColor m_Color;
    QPainter* painter;
    
};

#endif // COLORLABEL_H
