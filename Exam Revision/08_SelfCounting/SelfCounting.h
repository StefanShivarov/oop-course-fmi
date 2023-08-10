#pragma once

class SelfCounting {

	const int const_val;

	static unsigned liveObjectsCount;
	static unsigned createdObjectsCount;

public:

	SelfCounting();
	SelfCounting(int val);
	SelfCounting(const SelfCounting& other);
	~SelfCounting();

	static unsigned getLiveObjectsCount();
	static unsigned getCreatedObjectsCount();
};