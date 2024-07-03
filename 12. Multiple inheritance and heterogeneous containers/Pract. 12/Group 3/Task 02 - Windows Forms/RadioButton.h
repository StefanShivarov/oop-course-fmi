#pragma once
#include "Control.h"
#include "MyString.h"
#include "Vector.hpp"

class RadioButton : public Control
{
public:
    RadioButton() = default;
    RadioButton(const Size& size, const Location& location, const Vector<MyString>& options);

    const Vector<MyString>& getOptions() const;
    const MyString& getSelectedOption() const;

    void setDataDialog() override;
    Control* clone() const override;

private:
    Vector<MyString> options;
    int selectedOptionIndex = -1;
};
