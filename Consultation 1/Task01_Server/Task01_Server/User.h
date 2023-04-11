#pragma once
#include <fstream>

class User
{
private:
	char* username = nullptr;
	char* password = nullptr;
	mutable size_t accessCount = 0;

public:

	User() = default;
	User(const char* username, const char* password);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	const char* getUsername() const;
	size_t getAccessCount() const;

	void setUsername(const char* newUsername);
	void setPassword(const char* newPassword);
	void setAccessCount(size_t newCount);

	void readFromBinaryFile(std::ifstream& ifs);
	void writeToBinaryFile(std::ofstream& ofs) const;

private: 
	void free();
	void copyFrom(const User& other);
};

