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

    QMainWindow wnd;
    wnd.setWindowTitle("Lab_W_1");
    wnd.setGeometry(300, 300, 600, 300);
    QWidget centralWidget(&wnd);
    QVBoxLayout layout;
    MainLogic app;
    QLabel label1;
    QLabel label2;
    label1.setText(QString::number(getHour()) + ":" + QString::number(getMin()) + ":" + QString::number(getMs()));
    label2.setText(QString::number(getYear()) + "." + QString::number(getMonth() +  1) + "." + QString::number(getYDay()));
    QFont font("Arial", 20);
    label1.setFont(font);
    label2.setFont(font);
    layout.setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignCenter);
    layout.addWidget(&label1);
    layout.addWidget(&label2);
    app.execute(layout);
    centralWidget.setLayout(&layout);
    wnd.setCentralWidget(&centralWidget);
    wnd.show();
    return a.exec();
}
