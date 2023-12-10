#include "../include/inputitem.h"

InputItem::InputItem(QWidget* parent):QLineEdit(parent)
{
    setMaxLength(20);
}
