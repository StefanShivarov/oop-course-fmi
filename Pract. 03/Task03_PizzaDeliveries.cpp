#include <iostream>
#include <fstream>
#include <cstring>

struct PizzaDelivery {

	char customerPhoneNumber[20];
	char address[150];
	char pizzaType[30];
	int quantity;
	double price;
};

void writeDeliveryToBinaryFile(const char* filePath, const PizzaDelivery& delivery) {

	std::ofstream ofs(filePath, std::ios::binary);

	if (!ofs.is_open()) {
		std::cout << "Error! Can't open file for writing!" << std::endl;
		return;
	}

	ofs.write((const char*) &delivery, sizeof(PizzaDelivery));

	ofs.close();
}

void readDeliveryFromBinaryFile(const char* filePath, PizzaDelivery& delivery) {

	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {

		std::cout << "Error! Can't open file for reading!" << std::endl;
		return;
	}

	ifs.read((char*)&delivery, sizeof(PizzaDelivery));
	ifs.close();
}

void sortDeliveriesByAddress(PizzaDelivery* deliveries, int deliveriesAmount) {

	for (int i = 0; i < deliveriesAmount - 1; i++) {

		if (strcmp(deliveries[i].address, deliveries[i + 1].address) > 0) {
			PizzaDelivery temp = deliveries[i];
			deliveries[i] = deliveries[i + 1];
			deliveries[i + 1] = temp;
		}
	}
}

PizzaDelivery* readAllDeliveriesFromBinaryFile(const char* filePath, int &arrSize) {

	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {
		throw std::exception("Error!");
	}

	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();
	arrSize = fileSize / sizeof(PizzaDelivery);

	PizzaDelivery* deliveries = new PizzaDelivery[arrSize];

	ifs.seekg(0, std::ios::beg);
	ifs.read((char*) deliveries, arrSize * sizeof(PizzaDelivery));

	ifs.close();
	return deliveries;
}

void saveSortedDeliveriesToBinaryFile(const char* sourceFilePath, const char* sortedFilePath) {

	int arrSize = 0;
	PizzaDelivery* deliveries = readAllDeliveriesFromBinaryFile(sourceFilePath, arrSize);

	sortDeliveriesByAddress(deliveries, arrSize);

	for (int i = 0; i < arrSize; i++) {

		writeDeliveryToBinaryFile(sortedFilePath, deliveries[i]);
	}

	delete[] deliveries;
}

void printDeliveryToConsole(const PizzaDelivery& delivery) {

	std::cout << "Address: " << delivery.address << '\n'
		<< "Phone: " << delivery.customerPhoneNumber << '\n'
		<< "Pizza: " << delivery.pizzaType << '\n'
		<< "Quantity: " << delivery.quantity << '\n'
		<< "Price: " << delivery.price << '\n';
}

void readDeliveryFromConsole(PizzaDelivery& delivery) {

	std::cout << "Enter address: ";
	std::cin.getline(delivery.address, 150);
	std::cout << "Enter phone number: ";
	std::cin.getline(delivery.customerPhoneNumber, 20);
	std::cout << "Enter pizza type: ";
	std::cin.getline(delivery.pizzaType, 30);
	std::cout << "Enter quantity ";
	std::cin >> delivery.quantity;
	std::cout << "Enter price ";
	std::cin >> delivery.price;
}

int main() {

	//...
}