#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QVector>
#include <QString>
#include <ctime>
#include "MainLogic.h"
#include "workWithTime.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainLogic app;
       app.execute(a);
    return a.exec();
}
