#include "CheckBox.h"

CheckBox::CheckBox(const Size& size, const Location& location, const MyString& text, bool checked) 
    : TextBox(size, location, text), checked(checked) {}

void CheckBox::setDataDialog()
{
    checked = !checked;
}

void CheckBox::setText(const MyString& text)
{
    this->text = text;
}

Control* CheckBox::clone() const
{
    return new CheckBox(*this);
}
