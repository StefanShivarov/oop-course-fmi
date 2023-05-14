#include <iostream>
#include <fstream>

const char FILE_NAME[] = "result.txt";

void writeSumAndProductToFile(int a, int b, int c) {

	std::ofstream ofs(FILE_NAME);

	if (!ofs.is_open()) {
		return;
	}

	ofs << a + b + c << " " << a * b * c;
	ofs.close();
}

void readSumAndProductFromFile() {
	
	std::ifstream ifs(FILE_NAME);

	if (!ifs.is_open()) {
		return;
	}

	int sum, product;
	ifs >> sum >> product;
	std::cout << "Sum: " << sum << ", Product: " << product << std::endl;
	ifs.close();
}

int main() {

	int a, b, c;
	std::cin >> a >> b >> c;

	writeSumAndProductToFile(a, b, c);
	readSumAndProductFromFile();
}