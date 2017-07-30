#include "smartcode.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartCode w;
    w.show();

    return a.exec();
}
