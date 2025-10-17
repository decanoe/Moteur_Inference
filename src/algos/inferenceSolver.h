#pragma once
#include "../rule_base.h"
#include "../fact_base.h"

class InferenceSolver
{
public:
    virtual ~InferenceSolver() = default;
    virtual void run(const RuleBase& rule_base, FactBase& fact_base) = 0;
};