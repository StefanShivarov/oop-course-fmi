#pragma once
#include "TextBox.h"

class CheckBox : public TextBox
{
public:
    CheckBox() = default;
    CheckBox(const Size& size, const Location& location, const MyString& text, bool checked = false);

    void setDataDialog() override;

    void setText(const MyString& text);
    Control* clone() const override;
private:
    bool checked = false;
};
