#include "Player.h"

int Player::currentId = 1;

Player::Player() : Player(currentId, 0) {}

Player::Player(int id, unsigned points) : id(id), points(points), stars(Stars::ONE_STAR) {
    currentId++;
}

int Player::getId() const
{
    return id;
}

unsigned Player::getPoints() const
{
    return points;
}

Player::Stars Player::getStars() const
{
    return stars;
}

void Player::completeMission(unsigned missionPoints)
{
    points += missionPoints;
}

bool Player::levelUp()
{
    switch (stars) {
        case Stars::ONE_STAR:
            if (points >= 256) {
                points -= 256;
                stars = Stars::TWO_STARS;
            }
            return true;

        case Stars::TWO_STARS:
            if (points >= 512) {
                points -= 512;
                stars = Stars::THREE_STARS;
            }
            return true;

        case Stars::THREE_STARS:
            if (points >= 1024) {
                points -= 1024;
                stars = Stars::FOUR_STARS;
            }
            return true;

        case Stars::FOUR_STARS:
            if (points >= 2048) {
                points -= 2048;
                stars = Stars::FIVE_STARS;
            }
            return true;

        default:
            return false;
    }
}
