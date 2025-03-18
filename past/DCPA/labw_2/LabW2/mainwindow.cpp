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
    QAction* exe170 = new QAction(tr("&Process Text(170)"), this);
    QAction* exe182 = new QAction(tr("&Process Text(182)"), this);
    QAction* exe194 = new QAction(tr("&Process Text(194)"), this);
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu -> addAction(openAction);
    fileMenu -> addAction(saveAction);
    QMenu* processMenu = menuBar()->addMenu(tr("&Process"));
    processMenu -> addAction(exe170);
    processMenu -> addAction(exe182);
    processMenu -> addAction(exe194);
    //Button170 -> addAction(exe170);
    //Button182 -> addAction(exe182);
    //Button194 -> addAction(exe194);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(exe170, &QAction::triggered, this, &MainWindow::task170);
    connect(exe182, &QAction::triggered, this, &MainWindow::task182);
    connect(exe194, &QAction::triggered, this, &MainWindow::task194);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
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
void MainWindow::task170() {
    MainL res;
    QString str=textEdit->toPlainText();
    QStringList strList=str.split('\n');
    textEdit->setText(res.ex170(strList[0]));
}
void MainWindow::task182 () {
    MainL res;
    QString str=textEdit->toPlainText();
    QStringList strList=str.split('\n');
    textEdit->setText(res.ex182(strList[0]));
}
void MainWindow::task194 () {
    MainL res;
    textEdit->setText(res.ex194(textEdit->toPlainText()));
}
void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file."));
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();
}
MainWindow::~MainWindow()
{
    delete ui;
}
