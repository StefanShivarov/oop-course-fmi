#pragma once
#include "Size.h"
#include "Location.h"

class Control
{
public:
    Control() = default;
    Control(const Size& size, const Location& location);

    const Size& getSize() const;
    const Location& getLocation() const;

    void setSize(const Size& size);
    void setLocation(const Location& location);

    virtual void setDataDialog() = 0;
    virtual Control* clone() const = 0;

    virtual ~Control() = default;
private:
    Size size;
    Location location;
};
