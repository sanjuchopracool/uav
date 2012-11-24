#include "colorwidget.h"
#include "ui_colorwidget.h"
#include <QDebug>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorWidget)
{
    layout = new QGridLayout;
    ui->setupUi(this);
    colorVector = new QVector<QColor>(12);
    ptrVector = new QVector<ColorLabel*>(12);

    for( int i= 0 ; i < 4 ; i++)
    {
        for( int j=0; j < 3 ;j ++)
        {
            colorTextLabel = new QLabel("Curve " + QString::number( i*4 + j +1));
            colorTextLabel->setMaximumSize(this->minimumSizeHint());
            m_ColorLabel = new ColorLabel(0,colorVector->value(4 * i + j));
            ptrVector->insert(4*i + j,m_ColorLabel);
            layout->addWidget(colorTextLabel,i,2*j);
            layout->addWidget(m_ColorLabel , i , 2*j + 1);
        }
        this->ui->groupBox->setLayout(layout);
    }
}

ColorWidget::~ColorWidget()
{
    qDebug() << ptrVector->at(0)->getName();
    delete ui;
}
