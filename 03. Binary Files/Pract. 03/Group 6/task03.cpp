#include <iostream>
#include <fstream>

namespace Constants {
    const int MAX_NAME_LENGTH = 25;
    const int MAX_OFFERS_AMOUNT = 100;
}

struct JobOffer {
    char companyName[Constants::MAX_NAME_LENGTH]{};
    unsigned coworkers = 0;
    unsigned vacancyDays = 0;
    unsigned long long salary = 0;
};

void writeOffer(std::ostream& os, const JobOffer& offer) {
    os << offer.companyName << ' '
        << offer.coworkers << ' '
        << offer.vacancyDays << ' '
        << offer.salary << std::endl;
}

void saveOfferToFile(const char* filePath, const JobOffer& offer) {
    std::ofstream ofs(filePath);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << filePath << '!';
        return;
    }

    writeOffer(ofs, offer);
    ofs.close();
}

void printOffer(const JobOffer& offer) {
    writeOffer(std::cout, offer);
}

JobOffer readOffer(std::istream& is) {
    JobOffer offer;

    is >> offer.companyName
        >> offer.coworkers
        >> offer.vacancyDays
        >> offer.salary;

    return offer;
}

struct OfferDatabase {
    JobOffer offers[Constants::MAX_OFFERS_AMOUNT];
    unsigned offersAmount = 0;
};

void printAllOffers(const OfferDatabase& offerDatabase) {
    for (unsigned i = 0; i < offerDatabase.offersAmount; i++) {
        printOffer(offerDatabase.offers[i]);
    }
}

OfferDatabase loadOffersFromFile(const char* filePath) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << filePath << '!';
        return;
    }

    OfferDatabase offerDatabase;
    
    while (!ifs.eof()) {
        offerDatabase.offers[offerDatabase.offersAmount++] = readOffer(ifs);
    }

    return offerDatabase;
}

void filterOffers(const OfferDatabase& offerDatabase, unsigned long long minSalary) {
    for (unsigned i = 0; i < offerDatabase.offersAmount; i++) {
        if (offerDatabase.offers[i].salary >= minSalary) {
            printOffer(offerDatabase.offers[i]);
            std::cout << std::endl;
        }
    }
}

bool existsOffer(const OfferDatabase& offerDatabase, const char* companyName) {
    for (unsigned i = 0; i < offerDatabase.offersAmount; i++) {
        if (strcmp(offerDatabase.offers[i].companyName, companyName) == 0) {
            return true;
        }
    }
    return false;
}

void perfectOffer(const OfferDatabase& offerDatabase, unsigned maxCoworkers,
    unsigned minVacancyDays, unsigned long long minSalary) {
    for (unsigned i = 0; i < offerDatabase.offersAmount; i++) {
        if (offerDatabase.offers[i].coworkers <= maxCoworkers
            && offerDatabase.offers[i].vacancyDays >= minVacancyDays
            && offerDatabase.offers[i].salary >= minSalary) {
            printOffer(offerDatabase.offers[i]);
            std::cout << std::endl;
        }
    }
}

enum class RequestType {
    Add,
    Info,
    Search,
    Filter,
    Quit,
    Invalid
};

RequestType getRequestTypeFromSymbol(char symbol) {
    switch (symbol) {
        case 'a': return RequestType::Add;
        case 'i': return RequestType::Info;
        case 's': return RequestType::Search;
        case 'f': return RequestType::Filter;
        case 'q': return RequestType::Quit;
        default: return RequestType::Invalid;
    }
}

char getRequestTypeSymbol(RequestType type) {
    switch (type) {
        case RequestType::Add: return 'a';
        case RequestType::Info: return 'i';
        case RequestType::Search: return 's';
        case RequestType::Filter: return 'f';
        case RequestType::Quit: return 'q';
        case RequestType::Invalid: return '?';
    }
}

struct Request {
    RequestType type = RequestType::Invalid;
    JobOffer offerToAdd;
    char searchedCompanyName[Constants::MAX_NAME_LENGTH]{};
    unsigned long long minSalary = 0;
};

Request deserializeRequestFromBinaryFile(std::ifstream& ifs) {
    Request request;
    ifs.read((char*)&request, sizeof(Request));
    return request;
}

void serializeRequestToBinaryFile(std::ofstream& ofs, const Request& request) {
    ofs.write((const char*)&request, sizeof(Request));
}

Request readRequest(std::istream& is) {
    Request request;

    char requestTypeSymbol;
    is >> requestTypeSymbol;
    request.type = getRequestTypeFromSymbol(requestTypeSymbol);

    switch (request.type) {
        case RequestType::Add: {
            request.offerToAdd = readOffer(is);
            break;
        }
        case RequestType::Search: {
            is >> request.searchedCompanyName;
            break;
        }
        case RequestType::Filter: {
            is >> request.minSalary;
            break;
        }
    }

    return request;
}

void executeRequest(const Request& request, OfferDatabase& offers) {
    switch (request.type) {
        case RequestType::Add: {
            saveOfferToFile("offers.txt", request.offerToAdd);
            offers.offers[offers.offersAmount++] = request.offerToAdd;
            break;
        }
        case RequestType::Info: {
            printAllOffers(offers);
            break;
        }
        case RequestType::Search: {
            std::cout << existsOffer(offers, request.searchedCompanyName) ? "Exists" : "Doesn't exist";
            break;
        }
        case RequestType::Filter: {
            filterOffers(offers, request.minSalary);
            break;
        }
        case RequestType::Quit: {
            break;
        }
        case RequestType::Invalid: {
            std::cout << "Invalid request!";
            break;
        }
    }
}

void runSystem(unsigned requestsAmount) {
    std::ofstream requestsOfs("requests.dat", std::ios::binary);
    if (!requestsOfs.is_open()) {
        std::cerr << "Failed to open file requests.dat!";
        return;
    }

    OfferDatabase offerDatabase = loadOffersFromFile("offers.txt");

    for (unsigned i = 0; i < requestsAmount; i++) {
        Request request = readRequest(std::cin);
        serializeRequestToBinaryFile(requestsOfs, request);

        if (request.type == RequestType::Quit) {
            return;
        }

        executeRequest(request, offerDatabase);
    }

    requestsOfs.close();
}

int main() {
    unsigned requestsAmount;
    std::cin >> requestsAmount;
    runSystem(requestsAmount);
}
