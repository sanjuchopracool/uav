#include <QApplication>
#include "colorwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorWidget w;
    w.show();
    
    return a.exec();
}
