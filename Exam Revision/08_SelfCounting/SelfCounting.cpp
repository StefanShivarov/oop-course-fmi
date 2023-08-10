#include "SelfCounting.h"

unsigned SelfCounting::liveObjectsCount = 0;
unsigned SelfCounting::createdObjectsCount = 0;

SelfCounting::SelfCounting() : SelfCounting(0) {}

SelfCounting::SelfCounting(int val) : const_val(val) {

	liveObjectsCount++;
	createdObjectsCount++;
}

SelfCounting::~SelfCounting() {

	liveObjectsCount--;
}

SelfCounting::SelfCounting(const SelfCounting& other) {

	liveObjectsCount++;
	createdObjectsCount++;
}

unsigned SelfCounting::getLiveObjectsCount() {
	return liveObjectsCount;
}

unsigned SelfCounting::getCreatedObjectsCount() {
	return createdObjectsCount;
}