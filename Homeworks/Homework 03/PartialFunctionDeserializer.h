#pragma once
#include "PartialFunction.h"
#include <fstream>

class PartialFunctionDeserializer
{
public:
    static PartialFunction* deserializePartialFunctionFromBinaryFile(const char* fileName);
private:
    static const uint16_t MAX_N_VALUE = 32;
    static PartialFunction* deserializePartialFunctionByCriterionZero(std::ifstream& ifs, uint16_t N);
    static PartialFunction* deserializePartialFunctionByCriterionOne(std::ifstream& ifs, uint16_t N);
    static PartialFunction* deserializePartialFunctionByCriterionTwo(std::ifstream& ifs, uint16_t N);
    static PartialFunction* deserializePartialFunctionMax(std::ifstream& ifs, uint16_t N);
    static PartialFunction* deserializePartialFunctionMin(std::ifstream& ifs, uint16_t N);
};
