#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

const short MAX_LENGTH = 25;
const char* FILE_PATH = "jobOffers.dat";

struct JobOffer {

	char companyName[MAX_LENGTH + 1];
	int colleaguesAmount;
	int paidRestDays;
	long long salary;
};

JobOffer initOffer(const char* name, int colleagues, int days, long long salary) {

	JobOffer result;
	strcpy(result.companyName, name);
	result.colleaguesAmount = colleagues;
	result.paidRestDays = days;
	result.salary = salary;
	return result;
}


void writeJobOfferToBinaryFile(std::ofstream& ofs, const JobOffer& offer) {
	
	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
		//throw std::exception("Error!");
	}

	ofs.write((const char*) &offer, sizeof(offer));
}

void writeJobOfferToTextFile(std::ofstream& ofs, const JobOffer& offer) {

	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
	}

	ofs << offer.companyName 
		<< offer.colleaguesAmount 
		<< offer.paidRestDays 
		<< offer.salary 
		<< std::endl;
}

void readJobOfferFromBinaryFile(std::ifstream& ifs, JobOffer& offer) {

	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
	}
	ifs.read((char*) &offer, sizeof(offer));
}

void flushStream() {
	std::cin.clear();
	std::cin.ignore(255, '\n');
}

JobOffer readOfferFromConsole() {

	char name[MAX_LENGTH + 1];
	int colleagues = 0, restDays = 0;
	long long salary = 0;

	std::cout << "Enter company name: ";
	std::cin.getline(name, MAX_LENGTH + 1, '\n');
	std::cout << "Enter colleagues amount: ";
	std::cin >> colleagues;
	std::cout << "Enter paid rest days: ";
	std::cin >> restDays;
	std::cout << "Enter salary: ";
	std::cin >> salary;

	flushStream();
	return initOffer(name, colleagues, restDays, salary);
}

void printOffer(const JobOffer& offer) {

	std::cout << "Company name: " << offer.companyName << '\n'
		<< "Colleagues amount: " << offer.colleaguesAmount << '\n'
		<< "Paid rest days: " << offer.paidRestDays << '\n'
		<< "Salary: " << offer.salary << '\n';
}

void addOffer(const char* filePath) {

	std::ofstream ofs(filePath, std::ios::binary | std::ios::app);

	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
	}

	JobOffer offerToAdd = readOfferFromConsole();
	writeJobOfferToBinaryFile(ofs, offerToAdd);
	ofs.close();
}

void filterOffers(const char* filePath, long long minSalary) {

	std::ifstream ifs(filePath, std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
	}

	while (!ifs.eof()) {

		JobOffer offerToRead;
		readJobOfferFromBinaryFile(ifs, offerToRead);

		if (!ifs) {
			break;
		}

		if (offerToRead.salary >= minSalary) {
			printOffer(offerToRead);
		}
	}
	ifs.close();
}

bool existsOfferByCompany(const char* filePath, const char* companyName) {

	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
	}

	while (!ifs.eof()) {

		JobOffer offerToRead;
		readJobOfferFromBinaryFile(ifs, offerToRead);
		if (!ifs) {
			break;
		}

		if (strcmp(companyName, offerToRead.companyName) == 0) {
			ifs.close();
			return true;
		}
	}

	ifs.close();
	return false;
}

void printAllOffers(const char* filePath) {

	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
	}

	while (!ifs.eof()) {

		JobOffer offerToRead;
		readJobOfferFromBinaryFile(ifs, offerToRead);
		if (!ifs) {
			break;
		}

		printOffer(offerToRead);
	}

	ifs.close();
}

bool isPerfectOffer(const JobOffer& offer, int maxColleagues, int minRestDays, int minSalary) {
	return offer.colleaguesAmount <= maxColleagues
		&& offer.paidRestDays >= minRestDays
		&& offer.salary >= minSalary;
}

void perfectOffers(const char* filePath, int maxColleagues, int minRestDays, int minSalary) {

	std::ifstream ifs(filePath, std::ios::binary);
	std::ofstream perfectOffersFile("perfectOffers.txt", std::ios::app);

	if (!ifs || !perfectOffersFile) {
		std::cout << "Error!" << std::endl;
	}

	while (ifs) {

		JobOffer offerToRead;
		readJobOfferFromBinaryFile(ifs, offerToRead);

		if (!ifs) {
			break;
		}

		if (isPerfectOffer(offerToRead, maxColleagues, minRestDays, minSalary)) {
			writeJobOfferToTextFile(perfectOffersFile, offerToRead);
		}
	}

	ifs.close();
	perfectOffersFile.close();

}

void runProgram(const char* filePath = FILE_PATH) {

	bool running = true;

	while (running) {

		std::cout << "Enter command: ";
		char commandSymbol;
		std::cin >> commandSymbol;

		switch (commandSymbol) {

		case 'a':

			flushStream();
			addOffer(filePath);
			break;

		case 'i':

			printAllOffers(filePath);
			break;

		case 's':

			flushStream();
			char companyName[MAX_LENGTH + 1];
			std::cin.getline(companyName, MAX_LENGTH + 1, '\n');
			if (existsOfferByCompany(filePath, companyName)) {
				std::cout << "Offer exists." << std::endl;
			}
			else {
				std::cout << "Offer doesn't exist." << std::endl;
			}
			break;

		case 'f':

			long long salary;
			std::cin >> salary;
			filterOffers(filePath, salary);
			break;

		case 'q':

			std::cout << "Quitting...";
			running = false;
			break;

		default:
			std::cout << "Invalid command! Try again." << std::endl;
			break;
		}
	}
}

int main() {

	runProgram();
}