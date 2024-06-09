#pragma once
#include "BooleanExpression.h"
#include "UnaryOperation.h"
#include "BinaryOperation.h"
#include "Variable.h"

BooleanExpression* expressionFactory(StringView str)
{
    str = str.substr(1, str.length() - 2); // removes the first and last brackets

    if (str.length() == 1) {
        return new Variable(str[0]);
    }

    size_t bracketsCounter = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            bracketsCounter++;
        }
        else if (str[i] == ')') {
            bracketsCounter--;
        }
        else if (bracketsCounter == 0) {
            switch (str[i]) {
                case '!': return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '&': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '|': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '>': return new Implication(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            }
        }
    }
}