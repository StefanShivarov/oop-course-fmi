#pragma once
#include "Player.h"

const unsigned MAX_PASS_LENGTH = 8;
const char* DEFAULT_PASS = "0000";

class LoggedPlayer : public Player
{
public:
    LoggedPlayer();
    LoggedPlayer(int id, unsigned points, const char* password);

    bool login(int id, const char* password);

private:
    char password[MAX_PASS_LENGTH + 1];
    bool loggedIn = false;

    void setPassword(const char* pass);
};
