#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>

class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ColorLabel(QColor color=QColor(),QWidget *parent = 0);
    void setColor(QColor color) {m_Color = color;}
    QColor color() const {return m_Color;}
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    
signals:
    
public slots:
private:
    QColor m_Color;
    QPainter* painter;
    
};

#endif // COLORLABEL_H
