#pragma once
class Location
{
public:
    Location() = default;
    Location(int x, int y);

    int getX() const;
    int getY() const;
private:
    int x = 0;
    int y = 0;
};

