#include <iostream>
#include <fstream>

namespace Constants {
    const int MAX_NAME_LENGTH = 63;
    const int MAX_CITIES_AMOUNT = 20;
}

struct City {
    char name[Constants::MAX_NAME_LENGTH];
    unsigned citizensAmount = 0;
};

struct District {
    City cities[Constants::MAX_CITIES_AMOUNT];
    unsigned citiesAmount = 0;
};

void addCityToDistrict(District& district, const City& city) {
    district.cities[district.citiesAmount++] = city;
}

void serializeCity(std::ostream& os, const City& city) {
    os << city.name << std::endl << city.citizensAmount;
}

void serializeDistrict(std::ostream& os, const District& district) {
    os << district.citiesAmount;
    for (unsigned i = 0; i < district.citiesAmount; i++) {
        os << std::endl;
        serializeCity(os, district.cities[i]);
    }
}

void writeDistrictToFile(const char* fileName, const District& district) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "There was an error with opening the file.";
        return;
    }

    serializeDistrict(ofs, district);
    ofs.close();
}

City deserializeCity(std::istream& is) {
    City city;
    is.getline(city.name, Constants::MAX_NAME_LENGTH);
    is >> city.citizensAmount;
    return city;
}

District deserializeDistrict(std::istream& is) {
    District district;
    is >> district.citiesAmount;
    for (unsigned i = 0; i < district.citiesAmount; i++) {
        is.ignore();
        district.cities[i] = deserializeCity(is);
    }

    return district;
}

void readDistrictFromFile(const char* fileName, District& district) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "There was an error with opening the file.";
        return;
    }

    district = deserializeDistrict(ifs);
    ifs.close();
}

int main() {
    District district;
    addCityToDistrict(district, { "Sofia", 1500000 });
    addCityToDistrict(district, { "Burgas", 700000 });
    addCityToDistrict(district, { "Varna", 1000000 });

    writeDistrictToFile("districts.txt", district);
    
    District deserialized;
    readDistrictFromFile("districts.txt", deserialized);

    serializeDistrict(std::cout, deserialized);

    return 0;
}
