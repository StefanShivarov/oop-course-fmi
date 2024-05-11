#include "PremiumPlayer.h"
#include <iostream>
#pragma warning(disable: 4996)

PremiumPlayer::PremiumPlayer() : LoggedPlayer()
{
    setUsername("n/a");
}

PremiumPlayer::PremiumPlayer(int id, const char* username, const char* pass) : PremiumPlayer(id, 0, username, pass) {}

PremiumPlayer::PremiumPlayer(int id, unsigned points, const char* username, const char* pass) : LoggedPlayer(id, points, pass)
{
    setUsername(username);
}

PremiumPlayer::PremiumPlayer(const PremiumPlayer& other) : LoggedPlayer(other)
{
    copyFrom(other);
}

PremiumPlayer::PremiumPlayer(PremiumPlayer&& other) : LoggedPlayer(std::move(other))
{
    moveFrom(std::move(other));
}

PremiumPlayer& PremiumPlayer::operator=(const PremiumPlayer& other)
{
    if (this != &other) {
        LoggedPlayer::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

PremiumPlayer& PremiumPlayer::operator=(PremiumPlayer&& other) noexcept
{
    if (this != &other) {
        LoggedPlayer::operator=(std::move(other));
        free();
        copyFrom(other);
    }
    return *this;
}

PremiumPlayer::~PremiumPlayer()
{
    free();
}

bool PremiumPlayer::levelUp()
{
    switch (stars) {
    case Stars::ONE_STAR:
        if (points >= 256) {
            points -= 256;
            stars = Stars::TWO_STARS;
        }
        return true;

    case Stars::TWO_STARS:
        if (points >= 256) {
            points -= 256;
            stars = Stars::THREE_STARS;
        }
        return true;

    case Stars::THREE_STARS:
        if (points >= 256) {
            points -= 256;
            stars = Stars::FOUR_STARS;
        }
        return true;

    case Stars::FOUR_STARS:
        if (points >= 256) {
            points -= 256;
            stars = Stars::FIVE_STARS;
        }
        return true;

    default:
        return false;
    }
}

const char* PremiumPlayer::getUsername() const
{
    return username;
}

void PremiumPlayer::setUsername(const char* username)
{
    if (!username) {
        throw std::invalid_argument("Username is nullptr!");
    }
    delete[] this->username;
    this->username = new char[strlen(username) + 1];
    strcpy(this->username, username);
}

void PremiumPlayer::free()
{
    delete[] username;
    username = nullptr;
}

void PremiumPlayer::copyFrom(const PremiumPlayer& other)
{
    username = new char[strlen(other.username) + 1];
    strcpy(username, other.username);
}

void PremiumPlayer::moveFrom(PremiumPlayer&& other)
{
    username = other.username;
    other.username = nullptr;
}
