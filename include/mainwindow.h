#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace bmp = boost::multiprecision;

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
    void setRoundingNone();
    void setRoundingMathematical();
    void setRoundingBank();
    void setRoundingTruncate();

private:
    bmp::cpp_dec_float_50 parseFromString(const QString& stringValue);

    enum class Operation
    {
        Add = 0,
        Substract,
        Multiply,
        Divide
    };

    bmp::cpp_dec_float_50 calculate(const bmp::cpp_dec_float_50& lhs, const bmp::cpp_dec_float_50& rhs, const Operation& operation, bool& outOk);

    void round(bmp::cpp_dec_float_50& value);

    QString sanitize(const bmp::cpp_dec_float_50& value);

    enum class RoundingPolicy
    {
        None,
        Mathematical,
        Bank,
        Truncate
    };
    RoundingPolicy roundingPolicy = RoundingPolicy::None;

    static constexpr const int numberAmount = 4;
    static constexpr const int operatorAmount = 3;
    InputItem* numbers[numberAmount];
    OperatorItem* operators[operatorAmount];
    QLineEdit* output;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
