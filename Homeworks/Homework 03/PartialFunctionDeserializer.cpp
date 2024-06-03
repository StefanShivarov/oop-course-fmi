#include "PartialFunctionDeserializer.h"
#include "PartialFunctionMax.h"
#include "PartialFunctionMin.h"
#include "PartialFunctionByCriterion.h"

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionFromBinaryFile(const char* fileName)
{
    if (!fileName) {
        throw std::invalid_argument("File name is nullptr!");
    }

    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::exception("Failed to open file!");
    }

    uint16_t N, T;
    ifs.read((char*)&N, sizeof(N));
    if (N > MAX_N_VALUE) {
        throw std::invalid_argument("Count of arguments can't be higher than 32!");
    }
    ifs.read((char*)&T, sizeof(T));
    
    PartialFunction* resultFunction = nullptr;

    try {
        switch (T) {
            case 0: {
                resultFunction = deserializePartialFunctionByCriterionZero(ifs, N);
                break;
            }
            case 1: {
                resultFunction = deserializePartialFunctionByCriterionOne(ifs, N);
                break;
            }
            case 2: {
                resultFunction = deserializePartialFunctionByCriterionTwo(ifs, N);
                break;
            }
            case 3: {
                resultFunction = deserializePartialFunctionMax(ifs, N);
                break;
            }
            case 4: {
                resultFunction = deserializePartialFunctionMin(ifs, N);
                break;
            }
            default:
                throw std::invalid_argument("Invalid value for T!");
        }
    }
    catch (...) {
        ifs.close();
        throw;
    }
    
    ifs.close();
    return resultFunction;
}

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionByCriterionZero(std::ifstream& ifs, uint16_t N)
{
    int32_t* arguments = new int32_t[N];
    int32_t* results = new int32_t[N];
    try {
        ifs.read((char*)arguments, N * sizeof(int32_t));
        ifs.read((char*)results, N * sizeof(int32_t));
        PartialFunction* resultFunction = new PartialFunctionByCriterion<CriterionFunctionZero>(CriterionFunctionZero(arguments, results, N));
        delete[] arguments;
        delete[] results;
        return resultFunction;
    }
    catch (...) {
        delete[] arguments;
        delete[] results;
        throw;
    }
}

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionByCriterionOne(std::ifstream& ifs, uint16_t N)
{
    int32_t* undefinedArgs = new int32_t[N];
    try {
        ifs.read((char*)undefinedArgs, N * sizeof(int32_t));
        PartialFunction* resultFunction = new PartialFunctionByCriterion<CriterionFunctionOne>(CriterionFunctionOne(undefinedArgs, N));
        delete[] undefinedArgs;
        return resultFunction;
    }
    catch (...) {
        delete[] undefinedArgs;
        throw;
    }
}

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionByCriterionTwo(std::ifstream& ifs, uint16_t N)
{
    int32_t* args = new int32_t[N];
    try {
        ifs.read((char*)args, N * sizeof(int32_t));
        PartialFunction* resultFunction = new PartialFunctionByCriterion<CriterionFunctionTwo>(CriterionFunctionTwo(args, N));
        delete[] args;
        return resultFunction;
    }
    catch (...) {
        delete[] args;
        throw;
    }
}

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionMax(std::ifstream& ifs, uint16_t N)
{
    PartialFunctionMax* maxFunc = new PartialFunctionMax(N);
    try {
        for (uint16_t i = 0; i < N; i++) {
            char fileNameBuff[1024];
            ifs.getline(fileNameBuff, 1024, '\0');
            PartialFunction* func = deserializePartialFunctionFromBinaryFile(fileNameBuff);
            maxFunc->addFunction(func);
        }
        return maxFunc;
    }
    catch (...) {
        delete maxFunc;
        throw;
    }
}

PartialFunction* PartialFunctionDeserializer::deserializePartialFunctionMin(std::ifstream& ifs, uint16_t N)
{
    PartialFunctionMin* minFunc = new PartialFunctionMin(N);
    try {
        for (uint16_t i = 0; i < N; i++) {
            char fileNameBuff[1024];
            ifs.getline(fileNameBuff, 1024, '\0');
            PartialFunction* func = deserializePartialFunctionFromBinaryFile(fileNameBuff);
            minFunc->addFunction(func);
        }
        return minFunc;
    }
    catch (...) {
        delete minFunc;
        throw;
    }
}
