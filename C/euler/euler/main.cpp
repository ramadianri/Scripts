#include "mainwindow.h"
#include <QApplication>

#include <iostream>

using namespace std;

void euler(double x_0, double y_0, double x_n, double deltaX);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    euler(0, 1, 10, 0.1);

    return a.exec();
}
