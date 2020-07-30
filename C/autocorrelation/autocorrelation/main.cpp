#include "mainwindow.h"
#include <QApplication>
#include <string>

void Autocorrelation(const std::string& fileInputName, int tau_n);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Autocorrelation("data_Random.txt", 20);

    return a.exec();
}
