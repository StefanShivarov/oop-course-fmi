#pragma once
#include "ElectronicDevice.h"

class Laptop : public ElectronicDevice
{
public:
    Laptop();
    Laptop(const char* model, double price, double weight);

    double getWeight() const;
    void setWeight(double weight);

    ElectronicDevice* clone() const override;
private:
    double weight;
};

