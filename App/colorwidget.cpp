#include "colorwidget.h"
#include "ui_colorwidget.h"
#include <QDebug>

ColorWidget::ColorWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ColorWidget)
{
    layout = new QGridLayout;
    ui->setupUi(this);
    ptrVector = new QVector <ColorLabel*>(12);
    for( int i= 0 ; i < 4 ; i++)
    {
        for( int j=0; j < 3 ;j ++)
        {
            colorTextLabel = new QLabel("Curve " + QString::number( i*4 + j +1));
            colorTextLabel->setMaximumSize(this->minimumSizeHint());
            m_ColorLabel = new ColorLabel(0,QColor());
            ptrVector->replace(3*i+j,m_ColorLabel);
            layout->addWidget(colorTextLabel,i,2*j);
            layout->addWidget(m_ColorLabel , i , 2*j + 1);
        }
        this->ui->groupBox->setLayout(layout);
    }
    connect(ui->apply,SIGNAL(clicked()),this,SLOT(applyButtonSlot()));
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::getColor(QColor back, QColor text ,QVector<QColor>* vect)
{
    this->ui->backLabel->setColor(back);
    this->ui->textLabel->setColor(text);
    for(int k= 0 ; k <12 ; k++)
    {
        ptrVector->at(k)->setColor(vect->at(k));
    }
}

void ColorWidget::applyButtonSlot()
{
    QVector<QColor> colrVect(12);
    for(int i = 0 ; i < 12 ; i++)
    {
        colrVect.insert(i,ptrVector->at(i)->color());
    }
    emit setColor(this->ui->backLabel->color(),this->ui->textLabel->color(),colrVect);
}
