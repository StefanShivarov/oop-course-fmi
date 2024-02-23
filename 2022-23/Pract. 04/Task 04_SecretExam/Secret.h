#pragma once

const short MAX_DESC_LENGTH = 100;
const short MAX_PASS_LENGTH = 30;

class Secret
{

	char task[MAX_DESC_LENGTH + 1]{};
	char password[MAX_PASS_LENGTH + 1]{};
	mutable size_t loginFails = 0;

public:

	Secret() = default;
	Secret(const char* task, const char* password);

	const char* getTask(const char* pass) const;
	void setPassword(const char* newPassword, const char* oldPassword);
	void setTask(const char* newTask, const char* password);
	size_t getLoginFails() const;
};