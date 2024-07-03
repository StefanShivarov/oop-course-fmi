#pragma once
#include "Control.h"
#include "MyString.h"

class TextBox : public Control
{
public:
    TextBox() = default;
    TextBox(const Size& size, const Location& location, const MyString& text);

    const MyString& getText() const;

    void setDataDialog() override;
    Control* clone() const override;
protected:
    MyString text;
};

