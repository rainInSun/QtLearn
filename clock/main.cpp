#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    clockWidget w;
    w.startTimer();
    w.show();
    return a.exec();
}
