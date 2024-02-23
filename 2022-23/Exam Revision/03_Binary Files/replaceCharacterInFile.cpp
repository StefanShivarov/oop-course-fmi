#include <iostream>
#include <fstream>

void replaceCharacterInFile(char symbol, char replacement, std::fstream& file) {

	while (!file.eof()) {

		if (file.get() != symbol) {
			continue;
		}

		file.seekp(-1, std::ios::cur);
		file.put(replacement);
		file.flush();
	}
}

int main() {

	std::fstream file("replace.txt", std::ios::in | std::ios::out);

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	replaceCharacterInFile('a', '?', file);
	file.close();
}