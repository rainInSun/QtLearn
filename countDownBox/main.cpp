#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    countDownWidget w;
    w.show();
    w.startCountDown();
    return a.exec();
}
