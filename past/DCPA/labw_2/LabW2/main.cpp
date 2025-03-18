#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QtLogging>
#include <QDateTime>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
