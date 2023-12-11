#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class InputItem;
class OperatorItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showResult();
    void resetOutput();

private:
    static constexpr const int numberAmount = 4;
    static constexpr const int operatorAmount = 3;
    InputItem* numbers[numberAmount];
    OperatorItem* operators[operatorAmount];
    QLineEdit* output;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
