#pragma once
#include "ElectronicDevice.h"

class PC : public ElectronicDevice
{
public:
    PC();
    PC(const char* model, double price);

    ElectronicDevice* clone() const override;
};

