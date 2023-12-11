#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/inputitem.h"
#include "include/operatoritem.h"
#include "QGridLayout"
#include "QHBoxLayout"
#include "QRegularExpression"
#include "QRegularExpressionValidator"
#include "QLabel"

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

    QHBoxLayout* line1 = new QHBoxLayout();
    line1->addWidget(numbers[0]);
    line1->addWidget(operators[0]);
    line1->addWidget(numbers[1]);
    line1->addWidget(operators[1]);
    line1->addWidget(numbers[2]);
    line1->addWidget(operators[2]);
    line1->addWidget(numbers[3]);
    line1->addWidget(equals);
    line1->addWidget(output);

    QHBoxLayout* line2 = new QHBoxLayout();
    QGridLayout* layout = new QGridLayout();
    layout->addLayout(line1, 0, 5);
    centralWidget()->setLayout(layout);
    setWindowTitle("Финансовый калькулятор");
    QRegularExpression rx(R"((0|(-?[1-9]\d{0,2}(((\s\d{3})*)|(\d*))))([.,]\d+)?)");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
}

void MainWindow::resetOutput()
{
    output->setText("");
}

void MainWindow::showResult()
{

}
MainWindow::~MainWindow()
{
    delete ui;
}
