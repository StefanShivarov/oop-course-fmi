#include <iostream>
#include "Server.h"
#include "User.h"

int main()
{

	User u1("firstUser", "pass1");
	User u2("secondUser", "pass2");

	Server server;
	server.addUser(u1);
	server.addUser(u2);

	server.removeUser(u1.getUsername());

	server.writeToBinaryFile();

	server.printAllUsersInfo();
}
