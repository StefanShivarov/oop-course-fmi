#include "LoggedPlayer.h"
#include <iostream>
#pragma warning(disable: 4996)

LoggedPlayer::LoggedPlayer() : Player() {
    setPassword(DEFAULT_PASS);
}

LoggedPlayer::LoggedPlayer(int id, unsigned points, const char* password) : Player(id, points)
{
    setPassword(password);
}

bool LoggedPlayer::login(int id, const char* pass)
{
    return this->id == id && strcmp(password, pass) == 0;
}

void LoggedPlayer::setPassword(const char* pass)
{
    if (!pass) {
        throw std::invalid_argument("Password is nullptr!");
    }

    if (strlen(pass) > MAX_PASS_LENGTH) {
        throw std::invalid_argument("Password is way too long!");
    }

    strcpy(password, pass);
}
