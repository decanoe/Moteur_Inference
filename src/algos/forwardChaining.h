#pragma once
#include "inferenceSolver.h"

class ForwardChaining : public InferenceSolver
{
public:
    ForwardChaining(std::shared_ptr<Critere> critere) : InferenceSolver(critere) {}

    std::vector<std::shared_ptr<Rule>>::iterator GetRuleToApply(RuleBase &rule_base, FactBase &fact_base) {
        std::vector<std::shared_ptr<Rule>>::iterator result = rule_base.end();
        for (auto it_rules = rule_base.begin(); it_rules != rule_base.end();)
        {
            bool uselessRule = true;
            for (auto fact : (*it_rules)->get_consequents())
            {
                if (!fact_base.contains_fact(fact))
                {
                    uselessRule = false;
                    break;
                }
            }
            if (uselessRule)
            {
                it_rules = rule_base.remove_rule(it_rules);
                continue;
            }
            if ((*it_rules)->ruleValidated(fact_base))
            {
                if (result >= rule_base.end() || critere->betterThan(*it_rules, *result, fact_base))
                {
                    result = it_rules;
                }
            }
            ++it_rules;
        }
        return result;
    }
    void run(RuleBase &rule_base, FactBase &fact_base, std::shared_ptr<Fact> goal) override
    {
        bool goal_found = false;
        int rules_applied = 0;
        do
        {
            std::vector<std::shared_ptr<Rule>>::iterator rule_to_use = GetRuleToApply(rule_base, fact_base);
            if (rule_to_use == rule_base.end()) break;

            if ((*rule_to_use)->update_fact_base(fact_base))
            {
                std::cout << "- " << *rule_to_use << "\n";
                rules_applied++;
                if (goal != nullptr && (*rule_to_use)->contains_consequent(goal))
                {
                    std::cout << "Goal reached\n";
                    goal_found = true;
                    break;
                }
                rule_base.remove_rule(rule_to_use);
            }
            else break;
        } while (!rule_base.empty());

        if (rules_applied == 0)
        {
            std::cout << "no rules to apply\n";
        }
        else
        {
            std::cout << rules_applied << " rules applied\n";
        }

        if (goal != nullptr && !goal_found)
        {
            std::cout << "Goal not reached\n";
        }
        else if (goal == nullptr)
        {
            std::cout << "Fact base saturated\n";
        }
        std::cout << "Final fact base: \n" << fact_base << "\n";
    }
};