#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const Size& size, const Location& location, const MyString& text) : Control(size, location), text(text) {}

const MyString& TextBox::getText() const
{
    return text;
}

void TextBox::setDataDialog()
{
    std::cout << "Enter text: ";
    std::cin >> text;
}

Control* TextBox::clone() const
{
    return new TextBox(*this);
}
