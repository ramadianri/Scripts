#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<double> x,y;
    QFile textFile("data_psi.txt");
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
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    //ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    //assign data to it:
    ui->plot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("psi(x)");
    // set axes ranges, so we see all data:
    //ui->plot->xAxis->setRange(-5, 5);
    //ui->plot->yAxis->setRange(-1, 1);
    ui->plot->rescaleAxes(1);
    ui->plot->replot();


    QVector<double> xCorr,yCorr;
    QFile textFile2("data_psi_prob.txt");
    int lineCount2=0;
    if(textFile2.open(QIODevice::ReadOnly))
    {
        double xCorrStream,yCorrStream;
        QTextStream textStream2(&textFile2);
        while (!textStream2.atEnd()) {
            textStream2 >> xCorrStream >> yCorrStream;
            if(textStream2.status() == QTextStream::Ok){
                xCorr.append(xCorrStream);
                yCorr.append(yCorrStream);
            }
            else
                break;
            lineCount2++;
        }
    }

    // create a graph:
    ui->plot2->addGraph();
    //scatter style:
    ui->plot2->graph(0)->setPen(QPen(Qt::blue));
    ui->plot2->graph(0)->setLineStyle(QCPGraph::lsLine);
    //ui->plot2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    //assign data to it:
    ui->plot2->graph(0)->setData(xCorr, yCorr);
    // give the axes some labels:
    ui->plot2->xAxis->setLabel("x");
    ui->plot2->yAxis->setLabel("kebolehjadian");
    // set axes ranges, so we see all data:
    ui->plot2->rescaleAxes(1);
    ui->plot2->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}
