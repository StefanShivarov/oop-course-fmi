#pragma once
#include <iostream>

enum class DeviceType
{
    PC,
    LAPTOP,
    MOUSE,
    KEYBOARD
};

class ElectronicDevice
{
public:
    ElectronicDevice();
    ElectronicDevice(const char* model, double price);

    ElectronicDevice(const ElectronicDevice& other);
    ElectronicDevice(ElectronicDevice&& other) noexcept;

    ElectronicDevice& operator=(const ElectronicDevice& other);
    ElectronicDevice& operator=(ElectronicDevice&& other) noexcept;

    const char* getModel() const;
    void setModel(const char* model);

    const double getPrice() const;
    void setPrice(double price);

    virtual ~ElectronicDevice();
    virtual ElectronicDevice* clone() const = 0;
private:
    char* model;
    double price;

    void free();
    void copyFrom(const ElectronicDevice& other);
    void moveFrom(ElectronicDevice&& other) noexcept;
};
