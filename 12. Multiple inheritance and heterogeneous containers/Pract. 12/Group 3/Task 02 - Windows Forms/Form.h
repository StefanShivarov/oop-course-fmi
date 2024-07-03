#pragma once
#include "Control.h"
#include "MyString.h"

class Form
{
public:
    Form();
    Form(const Size& size, const MyString& name);
    Form(const Size& size, const MyString& name, const Control** controls, size_t controlsCount);

    Form(const Form& other);
    Form(Form&& other) noexcept;

    Form& operator=(const Form& other);
    Form& operator=(Form&& other) noexcept;

    ~Form();

    const MyString& getName() const;
    size_t getControlsCount() const;
    const Size& getSize() const;

    void addControl(const Control& control);
    void addControl(Control&& control);

    const Control* operator[](size_t index) const;

    void changeSizeAt(size_t index, const Size& size);
    void changeLocationAt(size_t index, const Location& location);
    void change(size_t index);

private:
    Size size;
    MyString name;
    Control** controls;
    size_t controlsCount;
    size_t controlsCapacity;
    
    void validateIndex(size_t index) const;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const Form& other);
    void copyControls(const Control** controls, size_t count);
    void moveFrom(Form&& other) noexcept;
};
