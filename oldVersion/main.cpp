#include "SSmartCode.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SSmartCode w;
    w.show();

    return a.exec();
}
