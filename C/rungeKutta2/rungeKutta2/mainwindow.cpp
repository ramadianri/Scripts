#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<double> x,y;
    QFile textFile("RK2_data.txt");
    int lineCount=0;
    if(textFile.open(QIODevice::ReadOnly))
    {
        double xStream,yStream;
        QTextStream textStream(&textFile);
        while (!textStream.atEnd()) {
            textStream >> xStream >> yStream;
            if(textStream.status() == QTextStream::Ok){
                x.append(xStream);
                y.append(yStream);
            }
            else
                break;
            lineCount++;
        }
    }

    // create a graph:
    ui->plot->addGraph();
    //scatter style:
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    //assign data to it:
    ui->plot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(0, 10);
    ui->plot->yAxis->setRange(0, 5);
    ui->plot->replot();


}

MainWindow::~MainWindow()
{
    delete ui;
}
