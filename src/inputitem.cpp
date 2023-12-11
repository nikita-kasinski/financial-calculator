#include "../include/inputitem.h"
#include "QRegularExpression"
#include "QRegularExpressionValidator"

InputItem::InputItem(QWidget* parent):QLineEdit(parent)
{
    setMaxLength(25);
    QRegularExpression rx(R"((0|(-?[1-9]\d{0,2}(((\s\d{3})*)|(\d*))))([.,]\d+)?)");
    validator = new QRegularExpressionValidator(rx, this);
    connect(this, &QLineEdit::textChanged, this, &InputItem::displayBorder);
    setText("0");
}

QValidator::State InputItem::validate()
{
    QString validationText = text();
    int cursorPosition = 0;
    return validator->validate(validationText, cursorPosition);
}

void InputItem::displayBorder(const QString &text)
{
    switch(validate())
    {
        case QValidator::State::Invalid:
            this->setStyleSheet("border: 2px solid red");
            break;
        case QValidator::State::Intermediate:
            this->setStyleSheet("border: 2px solid orange");
            break;
        case QValidator::State::Acceptable:
            this->setStyleSheet("border: 2px solid green");
            break;
    }
}
