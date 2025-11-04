#pragma once
#include "inferenceSolver.h"

class ForwardChaining : public InferenceSolver
{
public:
    ForwardChaining(std::shared_ptr<Critere> critere) : InferenceSolver(critere) {}

    void run(RuleBase &rule_base, FactBase &fact_base, std::shared_ptr<Fact> goal) override
    {
        std::vector<std::shared_ptr<Rule>> rules = rule_base.get_rules();
        bool newFact = false;
        do
        {
            std::cout << "Starting new iteration of forward chaining...\n";
            newFact = false;
            std::vector<std::shared_ptr<Rule>>::iterator rule_to_use = rules.begin();
            for (auto it_rules = std::next(rules.begin()); it_rules != rules.end(); it_rules++)
            {
                if ((*it_rules)->ruleValidated(fact_base))
                {
                    if (critere->betterThan(*it_rules, *rule_to_use))
                    {
                        rule_to_use = it_rules;
                        std::cout << "Nouvelle meilleure règle: " << **rule_to_use << "\n";
                    }
                }
            }
            if ((*rule_to_use)->update_fact_base(fact_base))
            {
                std::cout << "Applied rule: " << *rule_to_use << ", new facts inferred.\n";
                if (goal != nullptr && (*rule_to_use)->contains_consequent(goal))
                {
                    std::cout << "Goal fact found: " << goal << "\n";
                    break;
                }
                newFact = true;
                rules.erase(rule_to_use);
            }
        } while (!rules.empty() && newFact);
    } 
};