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
#include <boost/multiprecision/cpp_dec_float.hpp>

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
    output->setText("0");
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
