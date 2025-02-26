#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openFile();
    void saveFile();
    void task170();
    void task182();
    void task194();
private:
    Ui::MainWindow *ui;
    QLabel* text;
    QTextEdit* textEdit;
    QPushButton* Button170;
    QPushButton* Button182;
    QPushButton* Button194;
    QPushButton* saveButton;
    QPushButton* processButton;
};
#endif // MAINWINDOW_H
