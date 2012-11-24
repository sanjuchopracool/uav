#include <QApplication>
#include "colorlabel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorLabel w;
    w.show();
    
    return a.exec();
}
