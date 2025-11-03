#pragma once
#include "inferenceSolver.h"

class ForwardChaining : public InferenceSolver
{
public:
    void run(RuleBase& rule_base, FactBase& fact_base, std::shared_ptr<Fact> goal) override
    {
        bool butfound = false;
        std::vector<std::shared_ptr<Rule>> rules = rule_base.get_rules();
        bool newFact = false;
        do {
            bool newFact = false;
            for (auto it_rules = rules.begin(); it_rules != rules.end();)
            {
                std::cout << "Trying to apply rule: " << *it_rules << "\n";
                if ((*it_rules)->update_fact_base(fact_base))
                {  
                    std::vector<std::shared_ptr<Fact>> inferred_facts = (*it_rules)->get_consequents();
                    if (goal->findFact(inferred_facts)) {
                        butfound = true;
                        std::cout << "Goal fact found: " << goal << "\n";
                        break;
                    }
                    std::cout<< "Applied rule: " << *it_rules << ", new facts inferred.\n";
                    newFact = true;
                    it_rules = rules.erase(it_rules);
                }
                else {
                    ++it_rules;
                }
            }
        } while (butfound == false && !rules.empty() && newFact);
    }
};