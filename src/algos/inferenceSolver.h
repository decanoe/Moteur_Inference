#pragma once
#include "../rule_base.h"
#include "../fact_base.h"
#include "../criteres/critere.h"

class InferenceSolver
{
protected:
    std::shared_ptr<Critere> critere;
public:
    virtual ~InferenceSolver() = default;
    InferenceSolver(std::shared_ptr<Critere> critere): critere(critere) {}
    virtual void run(RuleBase& rule_base, FactBase& fact_base, std::shared_ptr<Fact> goal) = 0;
};