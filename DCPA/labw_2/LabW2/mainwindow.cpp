#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MainL.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction* openAction = new QAction(tr("&Open"), this);
    QAction* saveAction = new QAction(tr("&Save"), this);
    QAction* task170 = new QAction(tr("&Process Text"), this);
    QAction* task182 = new QAction(tr("&Process Text"), this);
    QAction* task194 = new QAction(tr("&Process Text"), this);

    connect(saveAction, &QAction::triggered, this, &Ui_MainWindow::saveFile);
    connect(task170, &QAction::triggered, this, &Ui_MainWindow::Button170);
    connect(task182, &QAction::triggered, this, &Ui_MainWindow::Button182);
    connect(task194, &QAction::triggered, this, &Ui_MainWindow::Button194);
}
void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file."));
        return;
    }

    QTextStream out(&file);
    out << text->text();
    file.close();
}
void MainWindow::Button170() {
    MainL res;
    text->setText(res.ex170(textEdit->toPlainText()));
}
void MainWindow::task170 () {

}
MainWindow::~MainWindow()
{
    delete ui;
}
