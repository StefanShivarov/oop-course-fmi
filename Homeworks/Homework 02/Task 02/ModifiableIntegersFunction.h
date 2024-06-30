#pragma once
#include <iostream>
#include <fstream>

typedef int16_t(*IntegersFunction)(int16_t);

class ModifiableIntegersFunction {
public:
    ModifiableIntegersFunction(IntegersFunction func);
    ModifiableIntegersFunction();

    bool setCustomOutput(int16_t input, int16_t output);
    void setExcluded(int16_t point, bool excluded);

    int16_t operator()(int16_t input) const;

    ModifiableIntegersFunction operator()(const ModifiableIntegersFunction& composed) const; // operator for composition

    ModifiableIntegersFunction operator^(int k) const;
    
    bool isInjective() const;
    bool isSurjective() const;
    bool isBijective() const;

    void deserializeFromBinaryFile(std::ifstream& ifs);
    void serializeToBinaryFile(std::ofstream& ofs) const;

    // void drawFunctionOnConsole() const;

    friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
    friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

private:
    struct FunctionPair {
        int16_t input = 0;
        int16_t output = 0;
        bool excluded = false;
    };

    class ResultCache {
    public:
        ResultCache();
        ResultCache(const ResultCache& other);
        ResultCache& operator=(const ResultCache& other);
        ~ResultCache();

        size_t size() const;

        bool insert(int16_t input, int16_t output);

        const FunctionPair* findByInput(int16_t input) const;
        const FunctionPair* findByOutput(int16_t output) const;
        void setExcluded(int16_t input, bool excluded);

        FunctionPair& operator[](size_t index);
        const FunctionPair& operator[](size_t index) const;

        void clear();

        void deserialize(std::ifstream& ifs);
        void serialize(std::ofstream& ofs) const;

    private:

        FunctionPair* pairs = nullptr;
        size_t pairsCount = 0;
        size_t capacity = 0;

        FunctionPair* findAt(int16_t input);

        void resize(size_t newCapacity);
        void free();
        void copyFrom(const ResultCache& other);
    };

    class FunctionCompositionContainer {
    public:
        FunctionCompositionContainer();
        FunctionCompositionContainer(const FunctionCompositionContainer& other);
        FunctionCompositionContainer& operator=(const FunctionCompositionContainer& other);
        ~FunctionCompositionContainer();

        void addFunction(const ModifiableIntegersFunction& func); // for some reason it doesn't let me pass a const MIF&
        // if I do , it forces me to make functions a const MIF**
        // but then I can't initialize it properly... :(

        const ModifiableIntegersFunction& operator[](size_t index) const;

        size_t size() const;
        bool empty() const;

    private:
        ModifiableIntegersFunction** functions = nullptr; // aggregation! Array of pointers to external resources!
        size_t capacity = 0;
        size_t functionsCount = 0;

        void free();
        void copyFrom(const FunctionCompositionContainer& other);
        void resize(size_t newCapacity);
    };

    mutable FunctionCompositionContainer compositionFunctions;
    mutable ResultCache resultCache;
    IntegersFunction func;
    bool reversed = false;
    mutable bool bijective = false;

    void fillUpCache() const;
};
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
