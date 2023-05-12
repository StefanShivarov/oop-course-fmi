#pragma once
#include "Player.h"
#include "MyString.h"

class User : public Player
{
private:

	static const size_t PASSWORD_MAX_LENGTH = 8;
	MyString password;
	bool isLoggedIn;

	void setPassword(const MyString& password);

public:

	User(int id, const MyString& password);

	void login(int id, const MyString& password);
};