#include <iostream>

const int MAX_RUNNERS_AMOUNT = 100;

struct Time {
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;
};

struct Runner {
    unsigned number = 0;
    Time time;
};

struct Race {
    Runner runners[MAX_RUNNERS_AMOUNT];
    unsigned runnersAmount = 0;
};

void readTimeFromFile(std::istream& is, Time& time) {
    is >> time.hours >> time.minutes >> time.seconds;
}

void readRunnerFromFile(std::istream& is, Runner& runner) {
    is >> runner.number;
    readTimeFromFile(is, runner.time);
}

void readRaceFromFile(std::istream& is, Race& race) {
    is >> race.runnersAmount;
    for (unsigned i = 0; i < race.runnersAmount; i++) {
        readRunnerFromFile(is, race.runners[i]);
    }
}

void writeTimeToFile(std::ostream& os, const Time& time) {
    os << time.hours << time.minutes << time.seconds;
}

void writeRunnerToFile(std::ostream& os, const Runner& runner) {
    os << runner.number;
    writeTimeToFile(os, runner.time);
}

void writeRaceToFile(std::ostream& os, const Race& race) {
    os << race.runnersAmount;
    for (unsigned i = 0; i < race.runnersAmount; i++) {
        os << std::endl;
        writeRunnerToFile(os, race.runners[i]);
    }
}

int main() {
    // ...
}
