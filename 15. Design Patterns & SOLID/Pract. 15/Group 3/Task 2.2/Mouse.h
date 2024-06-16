#pragma once
#include "ElectronicDevice.h"

class Mouse : public ElectronicDevice
{
public:
    Mouse();
    Mouse(const char* model, double price, unsigned dpi);

    unsigned getDPI() const;
    void setDPI(unsigned dpi);

    ElectronicDevice* clone() const override;
private:
    unsigned dpi;
};

