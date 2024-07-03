#include "RadioButton.h"

RadioButton::RadioButton(const Size& size, const Location& location, const Vector<MyString>& options) : Control(size, location), options(options) {}

const Vector<MyString>& RadioButton::getOptions() const
{
    return options;
}

const MyString& RadioButton::getSelectedOption() const
{
    if (selectedOptionIndex == -1) {
        return "";
    }

    return options[selectedOptionIndex];
}

void RadioButton::setDataDialog()
{
    std::cout << "Select option: ";
    std::cin >> selectedOptionIndex;
}

Control* RadioButton::clone() const
{
    return new RadioButton(*this);
}
