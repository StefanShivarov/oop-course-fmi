#pragma once
#include "ElectronicDevice.h"

class Keyboard : public ElectronicDevice
{
public:
    enum class KeyboardLayout 
    {
        AZERTY,
        QWERTY,
        QWERTZ,
        QZERTY
    };

    Keyboard();
    Keyboard(const char* model, double price, KeyboardLayout layout);

    KeyboardLayout getLayout() const;
    void setLayout(KeyboardLayout layout);

    ElectronicDevice* clone() const override;
private:
    KeyboardLayout layout;
};

