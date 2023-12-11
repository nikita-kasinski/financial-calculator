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

    QPushButton* calculateButton = new QPushButton(this);
    connect(calculateButton, &QPushButton::pressed, this, &MainWindow::showResult);

    QLabel* author = new QLabel(this);
    author->setText("Подготовил Касинский Никита 12 группа");

    QHBoxLayout* topLine = new QHBoxLayout;
    topLine->addWidget(numbers[0]);
    topLine->addWidget(operators[0]);
    topLine->addWidget(numbers[1]);
    topLine->addWidget(operators[1]);
    topLine->addWidget(numbers[2]);
    topLine->addWidget(operators[2]);
    topLine->addWidget(numbers[3]);
    topLine->addWidget(equals);
    topLine->addWidget(output);

    QHBoxLayout* middleLine = new QHBoxLayout;
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

MainWindow::~MainWindow()
{
    delete ui;
}
