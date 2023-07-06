#pragma once

enum class MagicCardType { unknown, trap, buff, spell };

class MagicCard
{

	char* name = nullptr;
	MagicCardType type = MagicCardType::unknown;

public:

	MagicCard() = default;
	MagicCard(const MagicCard& other);
	MagicCard& operator=(const MagicCard& other);
	~MagicCard();

	const char* getName() const;
	MagicCardType getType() const;

	void setName(const char* name);
	void setType(MagicCardType type);

private:

	void free();
	void copyFrom(const MagicCard& other);

};