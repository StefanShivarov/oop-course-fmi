#include "BooleanExpressionHandler.h"
#include <iostream>

BooleanExpressionHandler::BooleanExpressionHandler(const MyString& str)
{
    expr = expressionFactory(str);
}

BooleanExpressionHandler::BooleanExpressionHandler(const BooleanExpressionHandler& other)
{
    copyFrom(other);
}

BooleanExpressionHandler::BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept
{
    moveFrom(std::move(other));
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(const BooleanExpressionHandler& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(BooleanExpressionHandler&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

BooleanExpressionHandler::~BooleanExpressionHandler()
{
    free();
}

bool BooleanExpressionHandler::evaluate(const BooleanInterpretation& interpretation) const
{
    return expr->eval(interpretation);
}

bool BooleanExpressionHandler::isTautology() const
{
    return checkAllTruthAsssignments(true);
}

bool BooleanExpressionHandler::isContradiction() const
{
    return checkAllTruthAsssignments(false);
}

bool BooleanExpressionHandler::checkAllTruthAsssignments(bool value) const
{
    expr->populateVariables(variables);
    size_t variablesCount = variables.getTrueValuesCount();
    size_t powerOfTwo = 1 << variablesCount;
    for (size_t i = 0; i < powerOfTwo; i++) {
        BooleanInterpretation currentInterpretation = variables;
        currentInterpretation.excludeValuesByMask(i);
        if (expr->eval(currentInterpretation) != value) {
            return false;
        }
    }
    return true;
}

void BooleanExpressionHandler::free()
{
    delete expr;
    expr = nullptr;
}

void BooleanExpressionHandler::copyFrom(const BooleanExpressionHandler& other)
{
    expr = other.expr->clone();
}

void BooleanExpressionHandler::moveFrom(BooleanExpressionHandler&& other) noexcept
{
    expr = other.expr;
    other.expr = nullptr;
}
