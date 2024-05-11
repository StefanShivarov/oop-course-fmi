#pragma once
#include "LoggedPlayer.h"

class PremiumPlayer : public LoggedPlayer
{
public:
    PremiumPlayer();
    PremiumPlayer(int id, const char* username, const char* pass);
    PremiumPlayer(int id, unsigned points, const char* username, const char* pass);

    PremiumPlayer(const PremiumPlayer& other);
    PremiumPlayer(PremiumPlayer&& other) noexcept;

    PremiumPlayer& operator=(const PremiumPlayer& other);
    PremiumPlayer& operator=(PremiumPlayer&& other) noexcept;

    ~PremiumPlayer();

    bool levelUp() override;

    const char* getUsername() const;
    void setUsername(const char* username);

private:
    char* username;

    void free();
    void copyFrom(const PremiumPlayer& other);
    void moveFrom(PremiumPlayer&& other);
};
