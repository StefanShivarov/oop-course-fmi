#pragma once
class SelfCounting
{
public:
    SelfCounting();
    SelfCounting(int value);
    SelfCounting(const SelfCounting& other);
    ~SelfCounting();

    static unsigned getLiveObjectsCount();
    static unsigned getCreatedObjectsCount();

private:
    const int value;
    static unsigned liveObjectsCount;
    static unsigned createdObjectsCount;
};
