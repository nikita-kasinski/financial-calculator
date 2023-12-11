#ifndef INPUTITEM_H
#define INPUTITEM_H

#include <QLineEdit>
#include <QValidator>

class InputItem : public QLineEdit
{
public:
    InputItem(QWidget* parent = nullptr);
    QValidator::State validate();

private slots:
    void displayBorder(const QString &text);

private:
    QValidator* validator;
};

#endif // INPUTITEM_H
