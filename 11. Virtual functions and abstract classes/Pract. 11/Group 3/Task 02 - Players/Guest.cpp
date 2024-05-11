#include "Guest.h"

Guest::Guest(int id, unsigned points, unsigned timeLeft) : Player(id, points), timeLeft(timeLeft) {}

bool Guest::levelUp()
{
    return false;
}
