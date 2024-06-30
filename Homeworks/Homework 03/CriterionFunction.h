#pragma once
#include "Pair.hpp"

class CriterionFunction
{
public:
    CriterionFunction(const int32_t* args, uint16_t count);

    virtual Pair<bool,int32_t> operator()(int32_t x) const = 0;
    virtual CriterionFunction* clone() const = 0;
    virtual ~CriterionFunction() = default;
protected:
    static const uint16_t MAX_ARGS_COUNT = 32;
    int32_t args[MAX_ARGS_COUNT];
    uint16_t argsCount = 0;

    int findArgumentIndex(int32_t x) const;
};

class CriterionFunctionZero : public CriterionFunction
{
public:
    CriterionFunctionZero(const int32_t* args, const int32_t* results, uint16_t argsCount);

    Pair<bool, int32_t> operator()(int32_t x) const override;
    CriterionFunction* clone() const override;
private:
    int32_t results[MAX_ARGS_COUNT];
};

class CriterionFunctionOne : public CriterionFunction
{
public:
    CriterionFunctionOne(const int32_t* args, uint16_t count);

    Pair<bool, int32_t> operator()(int32_t x) const override;
    CriterionFunction* clone() const override;
};

class CriterionFunctionTwo : public CriterionFunction
{
public:
    CriterionFunctionTwo(const int32_t* args, uint16_t count);

    Pair<bool, int32_t> operator()(int32_t x) const override;
    CriterionFunction* clone() const override;
};
