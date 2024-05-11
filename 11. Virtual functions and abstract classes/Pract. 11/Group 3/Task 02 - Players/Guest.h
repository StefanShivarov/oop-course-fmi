#pragma once
#include "Player.h"

class Guest : public Player
{
public:
    Guest() = default;
    Guest(int id, unsigned points, unsigned timeLeft);

    bool levelUp() override;

private:
    unsigned timeLeft = 10;
};
