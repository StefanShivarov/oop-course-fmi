#pragma once
class Player
{
public:
    enum class Stars {
        ONE_STAR,
        TWO_STARS,
        THREE_STARS,
        FOUR_STARS,
        FIVE_STARS
    };

    Player();
    Player(int id, unsigned points);

    int getId() const;
    unsigned getPoints() const;
    Stars getStars() const;

    void completeMission(unsigned missionPoints);
    virtual bool levelUp();

    virtual ~Player() = default;

protected:
    int id;
    unsigned points;
    Stars stars;

private:
    static int currentId;
};
