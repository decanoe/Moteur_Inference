#pragma once
#include "inferenceSolver.h"

class ForwardChaining : public InferenceSolver
{
public:
    void run(const RuleBase& rule_base, FactBase& fact_base) override
    {
        std::vector<std::shared_ptr<Rule>> rules = rule_base.get_rules();
        bool newFact;
        do {
            bool newFact = false;
            for (auto it_rules = rules.begin(); it_rules != rules.end(); ++it_rules)
            {
                if ((*it_rules)->update_fact_base(fact_base))
                {
                    newFact = true;
                    rules.erase(it_rules);
                }
            }
        } while (!rules.empty() && newFact);
    }
};