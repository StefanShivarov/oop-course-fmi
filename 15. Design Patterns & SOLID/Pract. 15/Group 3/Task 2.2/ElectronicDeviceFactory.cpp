#include "ElectronicDeviceFactory.h"
#include <cstring>

static double parseDoubleFromString(const char* str)
{
    double result = 0.0;
    int len = strlen(str);
    bool hasDecimal = false;
    double decimalPlace = 1.0;
    bool negative = (str[0] == '-');
    size_t i = negative ? 1 : 0;

    for (; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10.0 + (str[i] - '0');
            if (hasDecimal) {
                decimalPlace *= 10.0;
            }
        }
        else if (str[i] == '.') {
            if (hasDecimal) {
                throw std::invalid_argument("Invalid argument: multiple decimal points found");
            }
            hasDecimal = true;
        }
        else {
            throw std::invalid_argument("Invalid argument: non-numeric character found");
        }
    }

    if (negative) {
        result = -result;
    }

    if (hasDecimal) {
        result /= decimalPlace;
    }

    return result;
}

static unsigned parseUnsignedFromString(const char* str)
{
    unsigned int result = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        else {
            throw std::invalid_argument("Invalid argument: non-digit character found");
        }
    }

    return result;
}

static Keyboard::KeyboardLayout parseKeyboardLayoutFromString(const char* str)
{
    if (strcmp(str, "AZERTY") == 0) {
        return Keyboard::KeyboardLayout::AZERTY;
    }
    else if (strcmp(str, "QWERTY")) {
        return Keyboard::KeyboardLayout::QWERTY;
    } 
    else if (strcmp(str, "QWERTZ")) {
        return Keyboard::KeyboardLayout::QWERTZ;
    }
    else if (strcmp(str, "QZERTY")) {
        return Keyboard::KeyboardLayout::QZERTY;
    }
    throw std::invalid_argument("Invalid keyboard layout!");
}

ElectronicDeviceFactory& ElectronicDeviceFactory::getInstance()
{
    static ElectronicDeviceFactory instance;
    return instance;
}

ElectronicDevice* ElectronicDeviceFactory::createElectronicDevice(DeviceType type)
{
    switch (type) {
        case DeviceType::PC: return new PC();
        case DeviceType::LAPTOP: return new Laptop();
        case DeviceType::MOUSE: return new Mouse();
        case DeviceType::KEYBOARD: return new Keyboard();
        default: throw new std::invalid_argument("Invalid device type!");
    }

}

ElectronicDevice* ElectronicDeviceFactory::createElectronicDevice(DeviceType type, const char* model,
                                                                    double price, const char* param)
{
    switch (type) {
        case DeviceType::PC: return new PC(model, price);
        case DeviceType::LAPTOP: return new Laptop(model, price, parseDoubleFromString(param));
        case DeviceType::MOUSE: return new Mouse(model, price, parseUnsignedFromString(param));
        case DeviceType::KEYBOARD: return new Keyboard(model, price, parseKeyboardLayoutFromString(param));
        default: throw new std::invalid_argument("Invalid device type!");
    }
}
