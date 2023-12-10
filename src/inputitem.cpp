#include "../include/inputitem.h"

InputItem::InputItem(QWidget* parent):QTextEdit(parent)
{
    setAcceptRichText(false);
    setLineWrapMode(LineWrapMode::NoWrap);
}
