#pragma once
#include "ElectronicDevice.h"
#include "PC.h"
#include "Laptop.h"
#include "Mouse.h"
#include "Keyboard.h"

class ElectronicDeviceFactory
{
public:
    ElectronicDeviceFactory(const ElectronicDeviceFactory& other) = delete;
    ElectronicDeviceFactory& operator=(const ElectronicDeviceFactory& other) = delete;

    static ElectronicDeviceFactory& getInstance();

    ElectronicDevice* createElectronicDevice(DeviceType type);
    ElectronicDevice* createElectronicDevice(DeviceType type, const char* model, double price, const char* param);
private:
    ElectronicDeviceFactory() = default;
    ~ElectronicDeviceFactory() = default;
};

