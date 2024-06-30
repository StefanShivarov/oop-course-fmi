#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>
#pragma warning(disable: 4996)

namespace Constants {
    const int MAX_NAME_LENGTH = 64;
    const int MAX_CONTENT_SIZE = 256;
    const int MAX_SONGS_COUNT = 30;
    const int DIFFERENT_GENRES_COUNT = 5;
    const int MAX_GENRE_COMBO_STR_LENGTH = 50;

    const unsigned SECONDS_IN_HOURS = 3600;
    const unsigned SECONDS_IN_MINUTE = 60;
}

namespace GenreSymbols {
    const char ROCK_SYMBOL = 'r';
    const char POP_SYMBOL = 'p';
    const char HIP_HOP_SYMBOL = 'h';
    const char ELECTRONIC_SYMBOL = 'e';
    const char JAZZ_SYMBOL = 'j';
}

namespace HelperFunctions {
    size_t getFileSize(std::ifstream& ifs);
    unsigned abs(int number);
}

size_t HelperFunctions::getFileSize(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t symbolsCount = ifs.tellg();
    ifs.seekg(currentPos);
    ifs.clear();

    return symbolsCount;
}

unsigned HelperFunctions::abs(int number) {
    return number < 0 ? (0 - number) : number;
}

//using the time class that we covered in seminars
class Time {
private:
    unsigned secondsFromMidnight = 0;

    bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier);

public:
    Time() = default;
    Time(unsigned hours, unsigned mins, unsigned seconds);

    unsigned getHours() const;
    unsigned getMins() const;
    unsigned getSeconds() const;

    bool setHours(unsigned hours);
    bool setMins(unsigned mins);
    bool setSeconds(unsigned seconds);

    void serialize(std::ostream& os) const;
    int compareTo(const Time& other) const;
};

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier) {
    if (newValue >= lowerBound && newValue <= upperBound) {
        (secondsFromMidnight -= (oldValue * multiplier)) += (newValue * multiplier);
        return true;
    }
    else {
        return false;
    }
}

Time::Time(unsigned hours, unsigned mins, unsigned seconds) {
    setHours(hours);
    setMins(mins);
    setSeconds(seconds);
}

unsigned Time::getHours() const {
    return secondsFromMidnight / Constants::SECONDS_IN_HOURS;
}

unsigned Time::getMins() const {
    return (secondsFromMidnight / 60) % 60;
}

unsigned Time::getSeconds() const {
    return secondsFromMidnight % 60;
}

bool Time::setHours(unsigned hours) {
    return validateAndSet(0, 23, hours, getHours(), Constants::SECONDS_IN_HOURS);
}

bool Time::setMins(unsigned mins) {
    return validateAndSet(0, 59, mins, getMins(), Constants::SECONDS_IN_MINUTE);
}

bool Time::setSeconds(unsigned seconds) {
    return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

void Time::serialize(std::ostream& os) const {
    os << std::setw(2) << std::setfill('0') << getHours() << ":"
        << std::setw(2) << std::setfill('0') << getMins() << ":"
        << std::setw(2) << std::setfill('0') << getSeconds();
}

int Time::compareTo(const Time& other) const {
    return secondsFromMidnight - other.secondsFromMidnight;
}

enum class Genre : unsigned char {
    UNDEFINED,
    ROCK = 1 << 0,
    POP = 1 << 1,
    HIP_HOP = 1 << 2,
    ELECTRONIC = 1 << 3,
    JAZZ = 1 << 4
};

typedef unsigned char GenreCombination;

Genre getGenreBySymbol(char symbol) {
    switch (symbol) {
        case GenreSymbols::ROCK_SYMBOL: return Genre::ROCK;
        case GenreSymbols::POP_SYMBOL: return Genre::POP;
        case GenreSymbols::HIP_HOP_SYMBOL: return Genre::HIP_HOP;
        case GenreSymbols::ELECTRONIC_SYMBOL: return Genre::ELECTRONIC;
        case GenreSymbols::JAZZ_SYMBOL: return Genre::JAZZ;
        default: return Genre::UNDEFINED;
    }
}

class Song {
    char name[Constants::MAX_NAME_LENGTH + 1]{};
    Time duration;
    GenreCombination genreCombination = 0;
    unsigned char content[Constants::MAX_CONTENT_SIZE]{};
    unsigned contentLength = 0;

    void getGenreCombinationStr(char* dest) const;
    bool setContent(const char* content);

public:
    Song() = default;
    Song(const char* name, const Time& duration, const char* genreComboStr);
    Song(const char* name, const Time& duration, const char* genreComboStr, const char* content);

    const char* getName() const;
    const Time& getDuration() const;

    bool hasGenre(Genre genre) const;
    void addGenre(Genre genre);

    bool setName(const char* name);
    bool setGenreCombination(const char* genreComboText);

    void readContentFromBinaryFile(std::ifstream& ifs);
    void saveContentToBinaryFile(std::ofstream& ofs) const;

    void mixWith(const Song& song);
    void addRhythm(unsigned k);

    void print() const;
};

void Song::getGenreCombinationStr(char* dest) const {
    std::stringstream ss;
    bool atLeastOneGenre = false;

    for (int i = 0; i < Constants::DIFFERENT_GENRES_COUNT; i++) {
        Genre genre = (Genre)(1 << i);
        if (hasGenre(genre)) {
            if (atLeastOneGenre) {
                ss << '&';
            }

            switch (genre) {
            case Genre::ROCK: ss << "Rock"; break;
            case Genre::POP: ss << "Pop"; break;
            case Genre::HIP_HOP: ss << "Hip-Hop"; break;
            case Genre::ELECTRONIC: ss << "Electronic"; break;
            case Genre::JAZZ: ss << "Jazz"; break;
            }

            atLeastOneGenre = true;
        }
    }

    strcpy(dest, ss.str().c_str());
}

bool Song::setContent(const char* content) {
    if (!content) {
        return false;
    }

    contentLength = strlen(content);
    if (contentLength > Constants::MAX_CONTENT_SIZE) {
        return false;
    }

    for (size_t i = 0; i < contentLength; i++) {
        this->content[i] = content[i];
    }
    return true;
}

Song::Song(const char* name, const Time& duration, const char* genreComboStr) : duration(duration) {
    setName(name);
    setGenreCombination(genreComboStr);
}

Song::Song(const char* name, const Time& duration, const char* genreComboStr, const char* content) : Song(name, duration, genreComboStr) {
    setContent(content);
}

const char* Song::getName() const {
    return name;
}

const Time& Song::getDuration() const {
    return duration;
}

bool Song::hasGenre(Genre genre) const {
    return (genreCombination & (unsigned char)genre) != 0;
}

void Song::addGenre(Genre genre) {
    genreCombination |= (unsigned char)genre;
}

bool Song::setName(const char* name) {
    if (!name) {
        return false;
    }

    size_t nameLength = strlen(name);
    if (nameLength > Constants::MAX_NAME_LENGTH) {
        return false;
    }

    strcpy(this->name, name);
    return true;
}

bool Song::setGenreCombination(const char* genreComboText) {
    if (!genreComboText) {
        return false;
    }

    size_t length = strlen(genreComboText);
    for (size_t i = 0; i < length; i++) {
        addGenre(getGenreBySymbol(genreComboText[i]));
    }
    return true;
}

void Song::readContentFromBinaryFile(std::ifstream& ifs) {
    contentLength = HelperFunctions::getFileSize(ifs);
    ifs.read((char*)&content, contentLength);
}

void Song::saveContentToBinaryFile(std::ofstream& ofs) const {
    ofs.write((const char*)&content, contentLength);
}

void Song::mixWith(const Song& song) {
    unsigned minLength = std::min(contentLength, song.contentLength);
    for (unsigned i = 0; i < minLength; i++) {
        content[i] ^= song.content[i];
    }
}

void Song::addRhythm(unsigned k) {
    unsigned shift = k - 1;
    int i = contentLength - 1;
    while (i >= 0) {

        if (shift >= 8) {
            i--;
            shift = HelperFunctions::abs(8 - shift);
            continue;
        }

        content[i] |= (1 << shift);
        shift += k;
    }
}

void Song::print() const {
    std::cout << name << ", ";
    duration.serialize(std::cout);
    char genreCombinationStr[Constants::MAX_GENRE_COMBO_STR_LENGTH];
    getGenreCombinationStr(genreCombinationStr);
    std::cout << ", " << genreCombinationStr;
}

class Playlist {
    Song songs[Constants::MAX_SONGS_COUNT];
    unsigned songsCount = 0;

    bool loadSongContent(const char* fileName, Song& song) const;
    void sortSongs(bool (*isLess)(const Song&, const Song&));

public:
    Playlist() = default;

    void addSong(const Song& song);
    bool addSong(const char* name, unsigned hours, unsigned minutes, unsigned seconds,
                const char* genreCombo, const char* contentFileName);

    Song* findByName(const char* songName);
    const Song* findByName(const char* songName) const;

    Playlist findByGenre(Genre genre) const; //decided to return a playlist instead of a songs array, in order to avoid dynamic memory allocation 
    Playlist findByGenre(char singleGenreSymbol) const;

    void printAllSongs() const;

    void sortSongsByDuration();
    void sortSongsByName();

    bool save(const char* songName, const char* fileName) const;
    bool mix(const char* firstSongName, const char* secondSongName);
};

bool Playlist::loadSongContent(const char* fileName, Song& song) const {
    if (!fileName) {
        return false;
    }

    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return false;
    }

    song.readContentFromBinaryFile(ifs);
    ifs.close();
    return true;
}

void Playlist::sortSongs(bool (*isLess)(const Song&, const Song&)) {
    for (unsigned i = 0; i < songsCount - 1; i++) {
        unsigned minIndex = i;

        for (unsigned j = i + 1; j < songsCount; j++) {
            if (isLess(songs[j], songs[minIndex])) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(songs[i], songs[minIndex]);
        }
    }
}

void Playlist::addSong(const Song& song) {
    songs[songsCount++] = song;
}

bool Playlist::addSong(const char* name, unsigned hours, unsigned minutes, unsigned seconds,
    const char* genreCombo, const char* contentFileName) {
    if (!name || !genreCombo || !contentFileName || songsCount == Constants::MAX_SONGS_COUNT) {
        return false;
    }

    Song song(name, Time(hours, minutes, seconds), genreCombo);

    if (!loadSongContent(contentFileName, song)) {
        return false;
    }

    addSong(song);
    return true;
}

Song* Playlist::findByName(const char* songName) {
    for (unsigned i = 0; i < songsCount; i++) {
        if (strcmp(songs[i].getName(), songName) == 0) {
            return &songs[i];
        }
    }
    return nullptr;
}

const Song* Playlist::findByName(const char* songName) const {
    for (unsigned i = 0; i < songsCount; i++) {
        if (strcmp(songs[i].getName(), songName) == 0) {
            return &songs[i];
        }
    }
    return nullptr;
}

Playlist Playlist::findByGenre(Genre genre) const {
    //decided to return a playlist instead of a songs array, in order to avoid dynamic memory allocation 
    Playlist specificGenrePlaylist;

    for (unsigned i = 0; i < songsCount; i++) {
        if (songs[i].hasGenre(genre)) {
            specificGenrePlaylist.addSong(songs[i]);
        }
    }
    return specificGenrePlaylist;
}

Playlist Playlist::findByGenre(char singleGenreSymbol) const {
    return findByGenre(getGenreBySymbol(singleGenreSymbol));
}

void Playlist::printAllSongs() const {
    for (unsigned i = 0; i < songsCount; i++) {
        songs[i].print();
        std::cout << std::endl;
    }
}

void Playlist::sortSongsByDuration() {
    sortSongs([](const Song& lhs, const Song& rhs) { return lhs.getDuration().compareTo(rhs.getDuration()) < 0; });
}

void Playlist::sortSongsByName() {
    sortSongs([](const Song& lhs, const Song& rhs) { return strcmp(lhs.getName(), rhs.getName()) < 0; });
}

bool Playlist::save(const char* songName, const char* fileName) const {
    if (!songName || !fileName) {
        return false;
    }

    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return false;
    }

    const Song* songToSave = findByName(songName);
    if (!songToSave) {
        return false;
    }

    songToSave->saveContentToBinaryFile(ofs);
    ofs.close();
    return true;
}

bool Playlist::mix(const char* firstSongName, const char* secondSongName) {
    Song* firstSong = findByName(firstSongName);
    Song* secondSong = findByName(secondSongName);

    if (!firstSong || !secondSong) {
        return false;
    }

    firstSong->mixWith(*secondSong);
    return true;
}

int main() {
    /*Playlist p;
    p.addSong("Song 2", 0, 1, 55, "rp", "song2.dat");
    p.addSong("Song 1", 0, 1, 5, "p", "song1.dat");

    p.printAllSongs();

    p.sortSongsByName();
    p.printAllSongs();
    
    p.mix("Song 1", "Song 2");
    p.save("Song 1", "mixed.dat");

    p.addSong("Song 4", 0, 3, 21, "jp", "song4.dat");
    Song* song4 = p.findByName("Song 4");

    song4->addRhythm(5);
    p.save("Song 4", "newSong4.dat");

    p.sortSongsByDuration();
    p.printAllSongs();

    p.findByGenre('p').printAllSongs();*/
    return 0;
}
