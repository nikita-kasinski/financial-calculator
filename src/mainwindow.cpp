#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/inputitem.h"
#include "QGridLayout"
#include "QHBoxLayout"
#include "QRegularExpression"
#include "QRegularExpressionValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    edit1 = new InputItem(this);
    edit2 = new InputItem(this);
    edit3 = new InputItem(this);
    edit4 = new InputItem(this);
    QHBoxLayout* line1 = new QHBoxLayout();
    line1->addWidget(edit1);
    line1->addWidget(edit2);
    line1->addWidget(edit3);
    line1->addWidget(edit4);
    QGridLayout* layout = new QGridLayout();
    layout->addLayout(line1, 0, 5);
    centralWidget()->setLayout(layout);
    setWindowTitle("Финансовый калькулятор");
}

MainWindow::~MainWindow()
{
    delete ui;
}
