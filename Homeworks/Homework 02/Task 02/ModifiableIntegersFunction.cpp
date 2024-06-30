#include "ModifiableIntegersFunction.h"

void ModifiableIntegersFunction::ResultCache::free() {
    delete[] pairs;
    pairs = nullptr;
    pairsCount = 0;
    capacity = 0;
}

void ModifiableIntegersFunction::ResultCache::copyFrom(const ResultCache& other) {
    pairsCount = other.pairsCount;
    capacity = other.capacity;
    pairs = new FunctionPair[capacity];
    for (size_t i = 0; i < pairsCount; i++) {
        pairs[i] = other.pairs[i];
    }
}

void ModifiableIntegersFunction::ResultCache::resize(size_t newCapacity) {
    FunctionPair* resizedPairs = new FunctionPair[newCapacity];
    for (size_t i = 0; i < pairsCount; i++) {
        resizedPairs[i] = pairs[i];
    }
    delete[] pairs;
    pairs = resizedPairs;
    capacity = newCapacity;
}

ModifiableIntegersFunction::ResultCache::ResultCache() : capacity(16) {
    pairs = new FunctionPair[capacity];
}

ModifiableIntegersFunction::ResultCache::ResultCache(const ResultCache& other) {
    copyFrom(other);
}

ModifiableIntegersFunction::ResultCache& ModifiableIntegersFunction::ResultCache::operator=(const ResultCache& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ModifiableIntegersFunction::ResultCache::~ResultCache() {
    free();
}

size_t ModifiableIntegersFunction::ResultCache::size() const {
    return pairsCount;
}

ModifiableIntegersFunction::FunctionPair& ModifiableIntegersFunction::ResultCache::operator[](size_t index) {
    return pairs[index];
}

const ModifiableIntegersFunction::FunctionPair& ModifiableIntegersFunction::ResultCache::operator[](size_t index) const {
    return pairs[index];
}

void ModifiableIntegersFunction::ResultCache::clear() {
    pairsCount = 0;
}

void ModifiableIntegersFunction::ResultCache::deserialize(std::ifstream& ifs) {
    ifs.read((char*)&pairsCount, sizeof(pairsCount));
    ifs.read((char*)&capacity, sizeof(capacity));
    ifs.read((char*)&pairs, sizeof(FunctionPair) * pairsCount);
}

void ModifiableIntegersFunction::ResultCache::serialize(std::ofstream& ofs) const {
    ofs.write((const char*)&pairsCount, sizeof(pairsCount));
    ofs.write((const char*)&capacity, sizeof(capacity));
    ofs.write((const char*)&pairs, sizeof(FunctionPair) * pairsCount);
}

ModifiableIntegersFunction::FunctionPair* ModifiableIntegersFunction::ResultCache::findAt(int16_t point) {
    for (size_t i = 0; i < pairsCount; i++) {
        if (pairs[i].input == point) {
            return &pairs[i];
        }
    }
    return nullptr;
}

const ModifiableIntegersFunction::FunctionPair* ModifiableIntegersFunction::ResultCache::findByInput(int16_t point) const {
    for (size_t i = 0; i < pairsCount; i++) {
        if (pairs[i].input == point) {
            return &pairs[i];
        }
    }
    return nullptr;
}

const ModifiableIntegersFunction::FunctionPair* ModifiableIntegersFunction::ResultCache::findByOutput(int16_t output) const {
    for (size_t i = 0; i < pairsCount; i++) {
        if (pairs[i].output == output) {
            return &pairs[i];
        }
    }
    return nullptr;
}

bool ModifiableIntegersFunction::ResultCache::insert(int16_t input, int16_t output) {
    if (pairsCount >= capacity) {
        resize(2 * capacity);
    }

    pairs[pairsCount].input = input;
    pairs[pairsCount].output = output;
    pairsCount++;
    return true;
}

void ModifiableIntegersFunction::ResultCache::setExcluded(int16_t point, bool excluded) {
    FunctionPair* pair = findAt(point);
    if (pair) {
        pair->excluded = excluded;
    }
    else {
        if (pairsCount >= capacity) {
            resize(2 * capacity);
        }

        pairs[pairsCount].input = point;
        pairs[pairsCount].excluded = excluded;
        pairsCount++;
    }
}

void ModifiableIntegersFunction::fillUpCache() const {
    if (func == nullptr) {
        return;
    }

    resultCache.clear();
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        try {
            int16_t result = (*this)(i);
            resultCache.insert(i, func(i));
        }
        catch (const std::logic_error& e) {
            resultCache.setExcluded(i, true);
        }
    }
}

void ModifiableIntegersFunction::FunctionCompositionContainer::free() {
    delete[] functions;
    functions = nullptr;
    functionsCount = capacity = 0;
}

void ModifiableIntegersFunction::FunctionCompositionContainer::copyFrom(const FunctionCompositionContainer& other) {
    functionsCount = other.functionsCount;
    capacity = other.capacity;
    
    functions = new ModifiableIntegersFunction*[capacity];
    for (size_t i = 0; i < functionsCount; i++) {
        functions[i] = other.functions[i];
    }
}

void ModifiableIntegersFunction::FunctionCompositionContainer::resize(size_t newCapacity) {
    ModifiableIntegersFunction** resizedFunctions = new ModifiableIntegersFunction*[newCapacity];
    for (size_t i = 0; i < functionsCount; i++) {
        resizedFunctions[i] = functions[i];
    }
    delete[] functions;
    functions = resizedFunctions;
    capacity = newCapacity;
}

ModifiableIntegersFunction::FunctionCompositionContainer::FunctionCompositionContainer() : capacity(8), functionsCount(0) {
    functions = new ModifiableIntegersFunction * [capacity] {nullptr};
}

ModifiableIntegersFunction::FunctionCompositionContainer::FunctionCompositionContainer(const FunctionCompositionContainer& other) {
    copyFrom(other);
}

ModifiableIntegersFunction::FunctionCompositionContainer& 
ModifiableIntegersFunction::FunctionCompositionContainer::operator=(const FunctionCompositionContainer& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ModifiableIntegersFunction::FunctionCompositionContainer::~FunctionCompositionContainer() {
    free();
}

const ModifiableIntegersFunction& ModifiableIntegersFunction::FunctionCompositionContainer::operator[](size_t index) const {
    return *functions[index];
}

void ModifiableIntegersFunction::FunctionCompositionContainer::addFunction(const ModifiableIntegersFunction& func) {
    if (functionsCount == capacity) {
        resize(2 * capacity);
    }

    functions[functionsCount++] = &func; // ne znam kak da zaobikolq tozi problem :(
}

size_t ModifiableIntegersFunction::FunctionCompositionContainer::size() const {
    return functionsCount;
}

bool ModifiableIntegersFunction::FunctionCompositionContainer::empty() const {
    return functionsCount == 0;
}

ModifiableIntegersFunction::ModifiableIntegersFunction(IntegersFunction func) : func(func) {}

ModifiableIntegersFunction::ModifiableIntegersFunction() : ModifiableIntegersFunction([](int16_t x) { return x; }) {}

bool ModifiableIntegersFunction::setCustomOutput(int16_t input, int16_t output) {
    return resultCache.insert(input, output);
}

void ModifiableIntegersFunction::setExcluded(int16_t point, bool excluded) {
    resultCache.setExcluded(point, excluded);
}

int16_t ModifiableIntegersFunction::operator()(int16_t input) const {
    const FunctionPair* pair = resultCache.findByInput(input);

    if (pair) {
        if (reversed) {
            const FunctionPair* reversePair = resultCache.findByOutput(pair->input);
            if (reversePair && reversePair->excluded) {
                throw std::logic_error("The function is undefined at this point!");
            }
            return reversePair->input;
        }

        if (pair->excluded) {
            throw std::logic_error("The function is undefined at this point!");
        }

        return pair->output;
    }

    int16_t result;
    if (compositionFunctions.empty()) {
        result = func(input);
        resultCache.insert(input, result);
        return result;
    }

    result = input;
    for (size_t i = 0; i < compositionFunctions.size(); i++) {
        try {
            result = compositionFunctions[i](result);
        }
        catch (const std::logic_error& e) {
            resultCache.setExcluded(input, true);
            throw std::logic_error("The function is undefined at this point!");
        }
    }

    return result;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator()(const ModifiableIntegersFunction& other) const {
    ModifiableIntegersFunction composition(other);

    composition.compositionFunctions.addFunction(other);
    composition.compositionFunctions.addFunction(*this);

    return composition;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int k) const {
    if (k < -1 || k == 0) {
        throw std::invalid_argument("Invalid argument for operator^!");
    }

    if (k == -1) {
        if (!isBijective()) {
            throw std::logic_error("Function is not reversible!");
        }
        // reverse func
        ModifiableIntegersFunction reverseFunc(*this);
        reverseFunc.reversed = true;
        return reverseFunc;
    }

    ModifiableIntegersFunction selfComposed;
    for (size_t i = 1; i < k; i++) {
        selfComposed.compositionFunctions.addFunction(selfComposed);
    }
    return selfComposed;
}

bool ModifiableIntegersFunction::isInjective() const {
    bool* hasResult = new bool[UINT16_MAX + 1] {false};
    try {
        for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
            int16_t result = (*this)(i);
            if (hasResult[result]) {
                delete[] hasResult;
                return false;
            }

            hasResult[result] = true;
        }
    }
    catch (const std::logic_error& e) {
        delete[] hasResult;
        return false;
    }

    delete[] hasResult;
    return true;
}

bool ModifiableIntegersFunction::isSurjective() const {
    bool* hasResult = new bool[UINT16_MAX + 1] {false};
    try {
        for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
            int16_t result = (*this)(i);
            hasResult[result] = true;
        }
    }
    catch (const std::logic_error& e) {
        delete[] hasResult;
        return false;
    }

    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        if (!hasResult[i]) {
            delete[] hasResult;
            return false;
        }
    }

    delete[] hasResult;
    return true;
}

bool ModifiableIntegersFunction::isBijective() const {
    return bijective = (bijective || (isInjective() && isSurjective()));
}

void ModifiableIntegersFunction::deserializeFromBinaryFile(std::ifstream& ifs) {
    ifs.read((char*)&reversed, sizeof(reversed));
    ifs.read((char*)&bijective, sizeof(bijective));
    resultCache.deserialize(ifs);
}

void ModifiableIntegersFunction::serializeToBinaryFile(std::ofstream& ofs) const {
    fillUpCache();
    ofs.write((const char*)&reversed, sizeof(reversed));
    ofs.write((const char*)&bijective, sizeof(bijective));
    resultCache.serialize(ofs);
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
    ModifiableIntegersFunction sumFunc;
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        try {
            sumFunc.resultCache.insert(i, lhs(i) + rhs(i));
        }
        catch (const std::logic_error& e) {
            sumFunc.setExcluded(i, true);
        }
    }
    return sumFunc;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
    ModifiableIntegersFunction diffFunc;
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        try {
            diffFunc.resultCache.insert(i, lhs(i) - rhs(i));
        }
        catch (const std::logic_error& e) {
            diffFunc.setExcluded(i, true);
        }
    }
    return diffFunc;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        if (lhs(i) >= rhs(i)) {
            return false;
        }
    }
    return true;
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        if (lhs(i) != rhs(i)) {
            return false;
        }
    }
    return true;
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) {
    int16_t diff = lhs(0) - rhs(0);
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        try {
            if ((lhs(i) - rhs(i)) != diff) {
                return false;
            }
        }
        catch (const std::logic_error& e) {
            return false;
        }
    }
    return true;
}



