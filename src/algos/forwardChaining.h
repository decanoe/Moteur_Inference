#pragma once
#include "inferenceSolver.h"

class ForwardChaining : public InferenceSolver
{
public:
    void run(RuleBase& rule_base, FactBase& fact_base) override
    {
        std::vector<std::shared_ptr<Rule>> rules = rule_base.get_rules();
        bool newFact = false;
        do {
            bool newFact = false;
            for (auto it_rules = rules.begin(); it_rules != rules.end();)
            {
                std::cout << "Trying to apply rule: " << *it_rules << "\n";
                if ((*it_rules)->update_fact_base(fact_base))
                {
                    std::cout<< "Applied rule: " << *it_rules << ", new facts inferred.\n";
                    newFact = true;
                    it_rules = rules.erase(it_rules);
                }
                else {
                    ++it_rules;
                }
            }
        } while (!rules.empty() && newFact);
    }
};