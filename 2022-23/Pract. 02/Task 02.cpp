#include <iostream>
#include <fstream>

size_t lengthOfFile(const char* fileName) {

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return 0;
	}
	ifs.seekg(0, std::ios::end);
	size_t position = ifs.tellg();
	ifs.close();
	return position;
}

int main()
{
	std::cout << lengthOfFile("result.txt");
}