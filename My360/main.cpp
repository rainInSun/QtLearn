#include "my360.h"
#include "buttons.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget360 w;
    w.show();
    return a.exec();
}
