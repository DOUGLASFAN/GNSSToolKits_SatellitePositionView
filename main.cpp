#include "satellitepositionview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    satellitepositionview w;
    w.show();
    return a.exec();
}
