#pragma once
#include "User.h"

const short MAX_USERS_COUNT = 20;

class Server
{
private:
	User users[20];
	size_t usersAmount = 0;

public:

	void addUser(const User& user);
	void removeUser(const char* username);
	bool containsUser(const char* username) const;

	void printAllUsersInfo() const;
	void printMostAccessedUser() const;

	void readFromBinaryFile();
	void writeToBinaryFile() const;

private:
	size_t getUserIndexByUsername(const char* username) const;
	size_t getIndexOfMostAccessedUser() const;
};

