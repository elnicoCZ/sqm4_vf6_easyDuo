#include "easyduo.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EasyDuo w;
    w.showFullScreen();
    return a.exec();
}
