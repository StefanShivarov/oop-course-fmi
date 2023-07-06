#pragma once
class MonsterCard
{

	char* name = nullptr;
	unsigned attackPoints = 0;
	unsigned defensePoints = 0;

public:

	MonsterCard() = default;
	MonsterCard(const MonsterCard& other);
	MonsterCard& operator=(const MonsterCard& other);
	~MonsterCard();

	const char* getName() const;
	unsigned getAttackPoints() const;
	unsigned getDefensePoints() const;

	void setName(const char* name);
	void setAttackPoints(unsigned points);
	void setDefensePoints(unsigned points);

private:

	void free(); 
	void copyFrom(const MonsterCard& other);
};