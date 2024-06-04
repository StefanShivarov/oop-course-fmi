#pragma once
#include "PartialFunction.h"

class Command
{
public:
    virtual void execute(const PartialFunction* func) const = 0;
    virtual ~Command() = default;
};

class RegimeOne : public Command
{
public:
    virtual void execute(const PartialFunction* func) const override;
};

class RegimeTwo : public Command 
{
public:
    virtual void execute(const PartialFunction* func) const override;
};

class CommandFactory 
{
public:
    static Command* generateCommand();
};