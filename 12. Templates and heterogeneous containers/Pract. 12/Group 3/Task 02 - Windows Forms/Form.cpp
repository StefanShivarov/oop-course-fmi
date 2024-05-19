#include "Form.h"

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocBySize(size_t size)
{
    return std::max(roundToPowerOfTwo(size + 1), 16u);
}

Form::Form() : Form(Size(10, 10), "Form") {}

Form::Form(const Size& size, const MyString& name) : size(size), name(name), controlsCount(0)
{
    controlsCapacity = dataToAllocBySize(controlsCount);
    controls = new Control* [controlsCapacity];
}

Form::Form(const Size& size, const MyString& name, const Control** controls, size_t controlsCount) : size(size), name(name), controlsCount(controlsCount)
{
    controlsCapacity = dataToAllocBySize(controlsCount);
    copyControls(controls, controlsCount);
}

Form::Form(const Form& other)
{
    copyFrom(other);
}

Form::Form(Form&& other) noexcept
{
    moveFrom(std::move(other));
}

Form& Form::operator=(const Form& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Form& Form::operator=(Form&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Form::~Form()
{
    free();
}

const MyString& Form::getName() const
{
    return name;
}

size_t Form::getControlsCount() const
{
    return controlsCount;
}

const Size& Form::getSize() const
{
    return size;
}

void Form::addControl(const Control& control)
{
    if (controlsCount == controlsCapacity) {
        resize(controlsCapacity * 2);
    }
    controls[controlsCount++] = control.clone();
}

void Form::addControl(Control&& control)
{
    if (controlsCount == controlsCapacity) {
        resize(controlsCapacity * 2);
    }
    controls[controlsCount++] = std::move(control.clone());
}

const Control* Form::operator[](size_t index) const
{
    return controls[index];
}

void Form::changeSizeAt(size_t index, const Size& size)
{
    validateIndex(index);
    // validate if is inside form
    controls[index]->setSize(size);
}

void Form::changeLocationAt(size_t index, const Location& location)
{
    validateIndex(index);
    // validate if is inside form
    controls[index]->setLocation(location);
}

void Form::change(size_t index)
{
    validateIndex(index);
    controls[index]->setDataDialog();
}

void Form::validateIndex(size_t index) const
{
    if (index >= controlsCount) {
        throw std::out_of_range("Index out of range!");
    }
}

void Form::resize(size_t newCapacity)
{
    Control** resizedControls = new Control*[newCapacity];
    for (size_t i = 0; i < controlsCount; i++) {
        resizedControls[i] = controls[i];
    }
    delete[] controls;
    controls = resizedControls;
    controlsCapacity = newCapacity;
}

void Form::free()
{
    for (size_t i = 0; i < controlsCount; i++) {
        delete controls[i];
    }
    delete[] controls;
    controlsCount = controlsCapacity = 0;
}

void Form::copyControls(const Control** controls, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        this->controls[i] = controls[i]->clone();
    }
    controlsCount = count;
}

void Form::copyFrom(const Form& other)
{
    controls = new Control*[other.controlsCapacity];
    copyControls(other.controls, other.controlsCount);
    controlsCapacity = other.controlsCapacity;
    size = other.size;
    name = other.name;
}

void Form::moveFrom(Form&& other) noexcept
{
    controls = other.controls;
    other.controls = nullptr;
    controlsCapacity = other.controlsCapacity;
    other.controlsCapacity = 0;
    controlsCount = other.controlsCount;
    other.controlsCount = 0;
    size = other.size;
    name = other.name;
    other.name = "\0";
}
