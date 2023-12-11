#include "../include/inputitem.h"
#include "QRegularExpression"
#include "QRegularExpressionValidator"

InputItem::InputItem(QWidget* parent):QLineEdit(parent)
{
    setMaxLength(25);
    QRegularExpression rx(R"((0|(-?[1-9]\d{0,2}(((\s\d{3})*)|(\d*))))([.,]\d+)?)");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    this->setValidator(validator);
    setText("0");
}
