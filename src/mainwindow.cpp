#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/inputitem.h"
#include "include/operatoritem.h"
#include "QGridLayout"
#include "QHBoxLayout"
#include "QRegularExpression"
#include "QRegularExpressionValidator"
#include "QLabel"
#include "QPushButton"
#include "QRadioButton"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < numberAmount; ++i)
    {
        numbers[i] = new InputItem(this);
        connect(numbers[i], &QLineEdit::textEdited, this, &MainWindow::resetOutput);
    }

    for (int i = 0; i < operatorAmount; ++i)
    {
        operators[i] = new OperatorItem(this);
        connect(operators[i], &QComboBox::currentIndexChanged, this, &MainWindow::resetOutput);
    }

    output = new QLineEdit(this);
    output->setReadOnly(true);

    QLabel* equals = new QLabel(this);
    equals->setText("=");
    QLabel* leftparenthesis = new QLabel(this);
    leftparenthesis->setText("(");
    QLabel* rightparenthesis = new QLabel(this);
    rightparenthesis->setText(")");

    QPushButton* calculateButton = new QPushButton(this);
    calculateButton->setText("Посчитать");
    connect(calculateButton, &QPushButton::pressed, this, &MainWindow::showResult);

    QLabel* author = new QLabel(this);
    author->setText("Подготовил Касинский Никита 3 курс 12 группа 2023");

    QRadioButton* roundingNone = new QRadioButton(this);
    roundingNone->setText("Без округления");
    connect(roundingNone, &QRadioButton::toggled, this, &MainWindow::setRoundingNone);
    roundingNone->toggle();

    QRadioButton* roundingMathematical = new QRadioButton(this);
    roundingMathematical->setText("Математическое");
    connect(roundingMathematical, &QRadioButton::toggled, this, &MainWindow::setRoundingMathematical);

    QRadioButton* roundingBank = new QRadioButton(this);
    roundingBank->setText("Банковское");
    connect(roundingBank, &QRadioButton::toggled, this, &MainWindow::setRoundingBank);

    QRadioButton* roundingTruncate = new QRadioButton(this);
    roundingTruncate->setText("Усечение");
    connect(roundingTruncate, &QRadioButton::toggled, this, &MainWindow::setRoundingTruncate);

    QHBoxLayout* topLine = new QHBoxLayout;
    topLine->addWidget(numbers[0]);
    topLine->addWidget(operators[0]);
    topLine->addWidget(leftparenthesis);
    topLine->addWidget(numbers[1]);
    topLine->addWidget(operators[1]);
    topLine->addWidget(numbers[2]);
    topLine->addWidget(rightparenthesis);
    topLine->addWidget(operators[2]);
    topLine->addWidget(numbers[3]);
    topLine->addWidget(equals);
    topLine->addWidget(output);

    QHBoxLayout* middleLine = new QHBoxLayout;
    middleLine->addWidget(roundingNone);
    middleLine->addWidget(roundingMathematical);
    middleLine->addWidget(roundingBank);
    middleLine->addWidget(roundingTruncate);
    middleLine->addWidget(calculateButton);

    QHBoxLayout* bottomLine = new QHBoxLayout;
    bottomLine->addStretch(1);
    bottomLine->addWidget(author);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addStretch(1);
    layout->addLayout(topLine);
    layout->addLayout(middleLine);
    layout->addStretch(1);
    layout->addLayout(bottomLine);
    centralWidget()->setLayout(layout);
    setWindowTitle("Финансовый калькулятор");
    resize(1000, 600);
}

void MainWindow::resetOutput()
{
    output->setText("");
}

void MainWindow::showResult()
{
    for(int i = 0; i < numberAmount; ++i)
    {
        if (numbers[i]->validate() != QValidator::State::Acceptable)
        {
            QMessageBox::warning(this, "Ошибка", "Некоторые введенные числа не валидны");
            return;
        }
    }
    bmp::cpp_dec_float_50 decimalNumbers[numberAmount];
    for (int i = 0; i < numberAmount; ++i)
    {
        decimalNumbers[i] = parseFromString(numbers[i]->text());
    }

    bool bOk;
    bmp::cpp_dec_float_50 result = calculate(decimalNumbers[1], decimalNumbers[2], static_cast<Operation>(operators[1]->currentIndex()), bOk);
    if (!bOk)
    {
        return;
    }

    if (operators[0]->currentIndex() < 2 && operators[2]->currentIndex() >=2)
    {
        result = calculate(result, decimalNumbers[3], static_cast<Operation>(operators[2]->currentIndex()), bOk);
        if (!bOk)
        {
            return;
        }

        result = calculate(decimalNumbers[0], result, static_cast<Operation>(operators[0]->currentIndex()), bOk);
        if (!bOk)
        {
            return;
        }
    }
    else
    {
        result = calculate(decimalNumbers[0], result, static_cast<Operation>(operators[0]->currentIndex()), bOk);
        if (!bOk)
        {
            return;
        }

        result = calculate(result, decimalNumbers[3], static_cast<Operation>(operators[2]->currentIndex()), bOk);
        if (!bOk)
        {
            return;
        }
    }

    this->round(result);
    QString resultSpaced = this->space(result);
    output->setText(resultSpaced);
}

void MainWindow::round(bmp::cpp_dec_float_50& value)
{
    switch(roundingPolicy)
    {
        case RoundingPolicy::None:
            break;
        case RoundingPolicy::Mathematical:
            value = floor(value + 0.5);
            break;
        case RoundingPolicy::Bank:
        {
            value = floor(value);
            std::string stringValue = value.str();
            if ((stringValue[stringValue.length() - 1] - '0') %2 == 1)
            {
                value += 1;
            }
            break;
        }
        case RoundingPolicy::Truncate:
            value = floor(value);
    }
}

QString MainWindow::space(const bmp::cpp_dec_float_50& value)
{
    return QString::fromStdString(value.str());
}

bmp::cpp_dec_float_50 MainWindow::parseFromString(const QString& stringValue)
{
    QString intermediate = stringValue;
    intermediate.remove(" ");
    intermediate.replace(",", ".");
    return bmp::cpp_dec_float_50{intermediate.toStdString()};
}

bmp::cpp_dec_float_50 MainWindow::calculate(const bmp::cpp_dec_float_50& lhs, const bmp::cpp_dec_float_50& rhs, const Operation& operation, bool& outOk)
{
    bmp::cpp_dec_float_50 intermediate;
    outOk = true;
    switch(operation)
    {
        case Operation::Add:
            intermediate = lhs + rhs;
            break;
        case Operation::Substract:
            intermediate = lhs - rhs;
            break;
        case Operation::Multiply:
            intermediate = lhs * rhs;
            break;
        case Operation::Divide:
            if (rhs == 0)
            {
                QMessageBox::warning(this, "Ошибка", "Нельзя делить на ноль");
                outOk = false;
                return 0;
            }
            intermediate = lhs / rhs;
    }
    if (abs(intermediate) > bmp::cpp_dec_float_50{1000000000000})
    {
        QMessageBox::warning(this, "Ошибка", "Переполнение");
        outOk = false;
    }
    return intermediate;
}

void MainWindow::setRoundingNone()
{
    roundingPolicy = RoundingPolicy::None;
}

void MainWindow::setRoundingMathematical()
{
    roundingPolicy = RoundingPolicy::Mathematical;
}

void MainWindow::setRoundingBank()
{
    roundingPolicy = RoundingPolicy::Bank;
}

void MainWindow::setRoundingTruncate()
{
    roundingPolicy = RoundingPolicy::Truncate;
}

MainWindow::~MainWindow()
{
    delete ui;
}
