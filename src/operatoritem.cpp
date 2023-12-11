#include "../include/operatoritem.h"

OperatorItem::OperatorItem(QWidget* parent) : QComboBox(parent)
{
    this->addItem("+");
    this->addItem("-");
    this->addItem("*");
    this->addItem("/");
    this->setCurrentIndex(0);
}
