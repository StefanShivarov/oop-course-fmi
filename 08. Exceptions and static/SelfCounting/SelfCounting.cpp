#include "SelfCounting.h"

unsigned SelfCounting::liveObjectsCount = 0;
unsigned SelfCounting::createdObjectsCount = 0;

SelfCounting::SelfCounting() : SelfCounting(0) {}

SelfCounting::SelfCounting(int value) : value(value) 
{
    liveObjectsCount++;
    createdObjectsCount++;
}

SelfCounting::SelfCounting(const SelfCounting& other) : value(other.value)
{
    liveObjectsCount++;
    createdObjectsCount++;
}

SelfCounting::~SelfCounting()
{
    liveObjectsCount--;
}

unsigned SelfCounting::getLiveObjectsCount()
{
    return liveObjectsCount;
}

unsigned SelfCounting::getCreatedObjectsCount()
{
    return createdObjectsCount;
}
