#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

const short MAX_LENGTH = 128;
const short MAX_USERS_AMOUNT = 100;

const char REGISTER_COMMAND[] = "register";
const char LOGIN_COMMAND[] = "login";
const char EXIT_COMMAND[] = "exit";
const char FILE_NAME[] = "userSystem.txt";

struct User {

	char name[MAX_LENGTH + 1] = "";
	char email[MAX_LENGTH + 1] = "";
	char password[MAX_LENGTH + 1] = "";
};

struct System {

	User users[MAX_USERS_AMOUNT];
	size_t usersCount = 0;
};

void writeUserToFile(std::ofstream& file, User& user) {

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		//throw std::exception("Error!");
	}
	file << user.name << ' ' <<
		user.email << ' ' <<
		user.password << '\n';
}

void registerUser(std::ofstream& file, System& system) {

	User userToRegister;
	std::cout << "Enter name: " << std::endl;
	std::cin >> userToRegister.name;
	std::cout << "Enter email: " << std::endl;
	std::cin >> userToRegister.email;
	std::cout << "Enter password: " << std::endl;
	std::cin >> userToRegister.password;

	system.users[system.usersCount++] = userToRegister;
	writeUserToFile(file, userToRegister);
	std::cout << "Registration successful" << std::endl;
}

void login(System& system) {

	char inputEmail[MAX_LENGTH + 1];
	char inputPass[MAX_LENGTH + 1];

	std::cout << "Enter email:" << std::endl;
	std::cin >> inputEmail;
	std::cout << "Enter password:" << std::endl;
	std::cin >> inputPass;

	bool userExists = false;
	for (size_t i = 0; i < system.usersCount; i++) {

		if (strcmp(system.users[i].email, inputEmail) == 0 &&
			strcmp(system.users[i].password, inputPass) == 0) {

			userExists = true;
			break;
		}
	}

	std::cout << (userExists ? "Login successful" : "Wrong email or password!")
		<< std::endl;
}

void readSystemFromFile(System& system) {

	std::ifstream file(FILE_NAME);

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		//throw std::exception("Error!");
	}

	int counter = 0;
	while (file >> system.users[counter].name >>
		system.users[counter].email >>
		system.users[counter].password) {

		counter++;

		if (counter >= MAX_USERS_AMOUNT) {
			break;
		}
	}

	system.usersCount = counter;
	file.close();
}

void runSystem() {

	std::ofstream file("userSystem.txt", std::ios::app);

	System system;
	readSystemFromFile(system);

	while (true) {
		std::cout << "Enter command: " << std::endl << "\\>";

		char command[MAX_LENGTH + 1];
		std::cin >> command;

		if (strcmp(command, REGISTER_COMMAND) == 0) {
			registerUser(file, system);
		}
		else if (strcmp(command, LOGIN_COMMAND) == 0) {
			login(system);
		}
		else if (strcmp(command, EXIT_COMMAND) == 0) {
			break;
		}
		else {
			std::cout << "Invalid command! Try again." << std::endl;
		}
	}
	
	file.close();
}

int main() {

	runSystem();
}