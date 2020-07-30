#include "mainwindow.h"
#include <QApplication>

#include <iostream>

using namespace std;

void trotterSuzuki(int boundary, double delta_x, double time);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    trotterSuzuki(5,0.1,0.6);

    return a.exec();
}
