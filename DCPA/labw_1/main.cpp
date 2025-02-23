#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QVector>
#include <QString>
#include <ctime>
#include <QTimer>
#include "MainLogic.h"
#include "workWithTime.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainLogic app;
    QTimer * timer = new QTimer();
       app.execute(a);
     timer->deleteLater();
    return a.exec();
}
