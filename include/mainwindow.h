#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class InputItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    InputItem* edit1;
    InputItem* edit2;
    InputItem* edit3;
    InputItem* edit4;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
